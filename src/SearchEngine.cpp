#include "SearchEngine.h"
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QTextStream>
#include <QRegularExpression>
#include <QThread>
#include <QElapsedTimer>
#include <QStandardPaths>
#include <QDebug>
#include <QtConcurrent>
#include <QFuture>
#include <algorithm>

SearchEngine::SearchEngine(QObject *parent)
    : QObject(parent)
    , m_isSearching(0)
    , m_searchCancelled(0)
    , m_maxResults(10000)
    , m_maxDepth(100)
    , m_timeoutMs(30000)
    , m_threadCount(QThread::idealThreadCount())
    , m_indexBuilt(false)
    , m_lastSearchTime(0)
    , m_resultCount(0)
{
    // Initialize search timer
    m_searchTimer = new QTimer(this);
    m_elapsedTimer = new QElapsedTimer();
    
    // Initialize stop words
    m_stopWords << "the" << "a" << "an" << "and" << "or" << "but" << "in" << "on" << "at" << "to" << "for" << "of" << "with" << "by";
    
    // Initialize file type extensions
    m_fileTypeExtensions["images"] = QStringList() << "jpg" << "jpeg" << "png" << "gif" << "bmp" << "tiff" << "svg";
    m_fileTypeExtensions["documents"] = QStringList() << "pdf" << "doc" << "docx" << "txt" << "rtf" << "odt";
    m_fileTypeExtensions["videos"] = QStringList() << "mp4" << "avi" << "mov" << "wmv" << "flv" << "mkv";
    m_fileTypeExtensions["audio"] = QStringList() << "mp3" << "wav" << "flac" << "aac" << "ogg" << "m4a";
    m_fileTypeExtensions["archives"] = QStringList() << "zip" << "rar" << "7z" << "tar" << "gz" << "bz2";
}

SearchEngine::~SearchEngine()
{
    if (m_isSearching.loadAcquire()) {
        cancelSearch();
    }
}

void SearchEngine::search(const QString &query, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.query = query;
    criteria.type = FileNameSearch;
    criteria.customPath = basePath;
    criteria.scope = basePath.isEmpty() ? CurrentDirectory : CustomPath;
    
    search(criteria);
}

void SearchEngine::search(const SearchCriteria &criteria)
{
    if (m_isSearching.loadAcquire()) {
        cancelSearch();
    }
    
    m_isSearching.storeRelease(1);
    m_searchCancelled.storeRelease(0);
    
    emit searchStarted(criteria.query);
    
    m_elapsedTimer->start();
    
    // Start search in separate thread
    QFuture<void> future = QtConcurrent::run([this, criteria]() {
        performSearch(criteria);
    });
    
    m_searchWatcher.setFuture(future);
    connect(&m_searchWatcher, &QFutureWatcher<void>::finished, this, &SearchEngine::onSearchFinished);
}

void SearchEngine::cancelSearch()
{
    m_searchCancelled.storeRelease(1);
    m_searchWatcher.cancel();
    m_isSearching.storeRelease(0);
    emit searchCancelled();
}

bool SearchEngine::isSearching() const
{
    return m_isSearching.loadAcquire();
}

void SearchEngine::performSearch(const SearchCriteria &criteria)
{
    QList<SearchResult> results;
    
    QString searchPath;
    switch (criteria.scope) {
    case CurrentDirectory:
        searchPath = QDir::currentPath();
        break;
    case HomeDirectory:
        searchPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        break;
    case CustomPath:
        searchPath = criteria.customPath;
        break;
    case EntireSystem:
        searchPath = "/";
        break;
    default:
        searchPath = QDir::currentPath();
        break;
    }
    
    searchInDirectory(searchPath, criteria, results);
    
    // Rank results by relevance
    rankResults(results, criteria);
    
    // Limit results
    if (results.size() > criteria.maxResults) {
        results = results.mid(0, criteria.maxResults);
    }
    
    m_resultCount = results.size();
    emit searchCompleted(results);
}

void SearchEngine::searchInDirectory(const QString &path, const SearchCriteria &criteria, QList<SearchResult> &results)
{
    if (m_searchCancelled.loadAcquire()) {
        return;
    }
    
    QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
    if (criteria.searchSubfolders) {
        flags |= QDirIterator::Subdirectories;
    }
    if (criteria.followSymlinks) {
        flags |= QDirIterator::FollowSymlinks;
    }
    
    QDir::Filters filters = QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot;
    if (criteria.searchHiddenFiles) {
        filters |= QDir::Hidden;
    }
    if (criteria.searchSystemFiles) {
        filters |= QDir::System;
    }
    
    QDirIterator iterator(path, filters, flags);
    
    while (iterator.hasNext() && !m_searchCancelled.loadAcquire()) {
        QString filePath = iterator.next();
        QFileInfo fileInfo(filePath);
        
        // Apply filters
        if (!matchesFilters(fileInfo, criteria)) {
            continue;
        }
        
        // Check if file matches search criteria
        bool matches = false;
        QStringList matchedLines;
        
        switch (criteria.type) {
        case FileNameSearch:
            matches = matchesFileName(fileInfo.fileName(), criteria);
            break;
        case ContentSearch:
            matches = matchesContent(filePath, criteria, matchedLines);
            break;
        case MetadataSearch:
            matches = matchesMetadata(fileInfo, criteria);
            break;
        case FuzzySearch:
            matches = fuzzyMatch(criteria.query, fileInfo.fileName());
            break;
        case RegexSearch:
            {
                QRegularExpression regex(criteria.query);
                matches = regex.match(fileInfo.fileName()).hasMatch();
            }
            break;
        default:
            matches = matchesFileName(fileInfo.fileName(), criteria);
            break;
        }
        
        if (matches) {
            SearchResult result;
            result.filePath = filePath;
            result.fileName = fileInfo.fileName();
            result.directory = fileInfo.dir().absolutePath();
            result.fileInfo = fileInfo;
            result.mimeType = m_mimeDatabase.mimeTypeForFile(filePath).name();
            result.lastModified = fileInfo.lastModified();
            result.fileSize = fileInfo.size();
            result.matchedLines = matchedLines;
            result.relevanceScore = calculateRelevanceScore(result, criteria);
            
            results.append(result);
            
            // Emit individual result
            emit resultFound(result);
            
            // Check if we've reached the maximum results
            if (results.size() >= criteria.maxResults) {
                break;
            }
        }
    }
}

bool SearchEngine::matchesFileName(const QString &fileName, const SearchCriteria &criteria)
{
    QString query = criteria.query;
    QString target = fileName;
    
    if (!criteria.caseSensitive) {
        query = query.toLower();
        target = target.toLower();
    }
    
    if (criteria.useRegex) {
        QRegularExpression regex(query);
        return regex.match(target).hasMatch();
    } else if (criteria.wholeWords) {
        QRegularExpression regex("\\b" + QRegularExpression::escape(query) + "\\b");
        return regex.match(target).hasMatch();
    } else {
        return target.contains(query);
    }
}

bool SearchEngine::matchesContent(const QString &filePath, const SearchCriteria &criteria, QStringList &matchedLines)
{
    if (!criteria.includeBinaryFiles && isBinaryFile(filePath)) {
        return false;
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    
    QString query = criteria.query;
    QString target = content;
    
    if (!criteria.caseSensitive) {
        query = query.toLower();
        target = target.toLower();
    }
    
    bool matches = false;
    if (criteria.useRegex) {
        QRegularExpression regex(query);
        matches = regex.match(target).hasMatch();
    } else if (criteria.wholeWords) {
        QRegularExpression regex("\\b" + QRegularExpression::escape(query) + "\\b");
        matches = regex.match(target).hasMatch();
    } else {
        matches = target.contains(query);
    }
    
    if (matches) {
        // Extract matching lines
        QStringList lines = content.split('\n');
        for (const QString &line : lines) {
            QString testLine = criteria.caseSensitive ? line : line.toLower();
            if (testLine.contains(query)) {
                matchedLines.append(line.trimmed());
                if (matchedLines.size() >= 10) { // Limit to 10 matching lines
                    break;
                }
            }
        }
    }
    
    return matches;
}

bool SearchEngine::matchesMetadata(const QFileInfo &fileInfo, const SearchCriteria &criteria)
{
    Q_UNUSED(fileInfo)
    Q_UNUSED(criteria)
    // This would check file metadata like tags, comments, etc.
    return false;
}

bool SearchEngine::matchesFilters(const QFileInfo &fileInfo, const SearchCriteria &criteria)
{
    // Size filter
    if (criteria.useSizeFilter) {
        qint64 fileSize = fileInfo.size();
        if (criteria.minSize > 0 && fileSize < criteria.minSize) {
            return false;
        }
        if (criteria.maxSize > 0 && fileSize > criteria.maxSize) {
            return false;
        }
    }
    
    // Date filter
    if (criteria.useDateFilter) {
        QDateTime modifiedTime = fileInfo.lastModified();
        if (criteria.dateFrom.isValid() && modifiedTime < criteria.dateFrom) {
            return false;
        }
        if (criteria.dateTo.isValid() && modifiedTime > criteria.dateTo) {
            return false;
        }
    }
    
    // File type filter
    if (!criteria.fileTypes.isEmpty()) {
        QString extension = fileInfo.suffix().toLower();
        bool matchesType = false;
        for (const QString &type : criteria.fileTypes) {
            if (m_fileTypeExtensions.contains(type)) {
                if (m_fileTypeExtensions[type].contains(extension)) {
                    matchesType = true;
                    break;
                }
            } else if (type.toLower() == extension) {
                matchesType = true;
                break;
            }
        }
        if (!matchesType) {
            return false;
        }
    }
    
    // Exclude patterns
    for (const QString &pattern : criteria.excludePatterns) {
        if (fileInfo.fileName().contains(pattern, Qt::CaseInsensitive)) {
            return false;
        }
    }
    
    return true;
}

double SearchEngine::calculateFuzzyScore(const QString &query, const QString &target)
{
    if (query.isEmpty() || target.isEmpty()) {
        return 0.0;
    }
    
    QString lowerQuery = query.toLower();
    QString lowerTarget = target.toLower();
    
    // Simple fuzzy matching using Levenshtein distance
    int maxLen = qMax(lowerQuery.length(), lowerTarget.length());
    int distance = 0;
    
    int minLen = qMin(lowerQuery.length(), lowerTarget.length());
    for (int i = 0; i < minLen; ++i) {
        if (lowerQuery[i] != lowerTarget[i]) {
            distance++;
        }
    }
    distance += qAbs(lowerQuery.length() - lowerTarget.length());
    
    return 1.0 - (double)distance / maxLen;
}

bool SearchEngine::fuzzyMatch(const QString &query, const QString &target, double threshold)
{
    return calculateFuzzyScore(query, target) >= threshold;
}

bool SearchEngine::isBinaryFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return true; // Assume binary if we can't read it
    }
    
    // Read first 1KB to check for null bytes
    QByteArray data = file.read(1024);
    file.close();
    
    return data.contains('\0');
}

double SearchEngine::calculateRelevanceScore(const SearchResult &result, const SearchCriteria &criteria)
{
    double score = 0.0;
    
    QString query = criteria.caseSensitive ? criteria.query : criteria.query.toLower();
    QString fileName = criteria.caseSensitive ? result.fileName : result.fileName.toLower();
    
    // Exact match gets highest score
    if (fileName == query) {
        score += 100.0;
    }
    // Starts with query
    else if (fileName.startsWith(query)) {
        score += 75.0;
    }
    // Contains query
    else if (fileName.contains(query)) {
        score += 50.0;
    }
    // Fuzzy match
    else {
        score += calculateFuzzyScore(query, fileName) * 25.0;
    }
    
    // Bonus for recent files
    qint64 daysSinceModified = result.lastModified.daysTo(QDateTime::currentDateTime());
    if (daysSinceModified < 7) {
        score += 10.0;
    } else if (daysSinceModified < 30) {
        score += 5.0;
    }
    
    return score;
}

void SearchEngine::rankResults(QList<SearchResult> &results, const SearchCriteria &criteria)
{
    Q_UNUSED(criteria)
    
    std::sort(results.begin(), results.end(), [](const SearchResult &a, const SearchResult &b) {
        return a.relevanceScore > b.relevanceScore;
    });
}

void SearchEngine::setMaxResults(int maxResults)
{
    m_maxResults = maxResults;
}

int SearchEngine::maxResults() const
{
    return m_maxResults;
}

void SearchEngine::setMaxDepth(int maxDepth)
{
    m_maxDepth = maxDepth;
}

int SearchEngine::maxDepth() const
{
    return m_maxDepth;
}

void SearchEngine::setTimeout(int timeoutMs)
{
    m_timeoutMs = timeoutMs;
}

int SearchEngine::timeout() const
{
    return m_timeoutMs;
}

void SearchEngine::setThreadCount(int threadCount)
{
    m_threadCount = threadCount;
}

int SearchEngine::threadCount() const
{
    return m_threadCount;
}

int SearchEngine::getLastSearchTime() const
{
    return m_lastSearchTime;
}

int SearchEngine::getResultCount() const
{
    return m_resultCount;
}

QString SearchEngine::getSearchStatistics() const
{
    return QString("Last search: %1ms, Results: %2").arg(m_lastSearchTime).arg(m_resultCount);
}

void SearchEngine::onSearchFinished()
{
    m_isSearching.storeRelease(0);
    m_lastSearchTime = m_elapsedTimer->elapsed();
}

void SearchEngine::onIndexingFinished()
{
    m_indexBuilt = true;
    emit indexingCompleted();
}

void SearchEngine::onSearchWorkerFinished()
{
    // Handle search worker completion
}

// Stub implementations for advanced features
void SearchEngine::searchByName(const QString &pattern, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.query = pattern;
    criteria.type = FileNameSearch;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::searchByContent(const QString &text, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.query = text;
    criteria.type = ContentSearch;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::searchByMetadata(const QHash<QString, QVariant> &metadata, const QString &basePath)
{
    Q_UNUSED(metadata)
    Q_UNUSED(basePath)
    // TODO: Implement metadata search
}

void SearchEngine::searchByRegex(const QRegularExpression &regex, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.query = regex.pattern();
    criteria.type = RegexSearch;
    criteria.useRegex = true;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::fuzzySearch(const QString &query, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.query = query;
    criteria.type = FuzzySearch;
    criteria.fuzzyMatching = true;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::searchByDateRange(const QDateTime &from, const QDateTime &to, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.type = DateSearch;
    criteria.useDateFilter = true;
    criteria.dateFrom = from;
    criteria.dateTo = to;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::searchBySizeRange(qint64 minSize, qint64 maxSize, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.type = SizeSearch;
    criteria.useSizeFilter = true;
    criteria.minSize = minSize;
    criteria.maxSize = maxSize;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::searchByType(const QStringList &mimeTypes, const QString &basePath)
{
    SearchCriteria criteria;
    criteria.type = TypeSearch;
    criteria.fileTypes = mimeTypes;
    criteria.customPath = basePath;
    search(criteria);
}

void SearchEngine::saveSearch(const SearchCriteria &criteria)
{
    Q_UNUSED(criteria)
    // TODO: Implement search history saving
}

QList<SearchEngine::SearchCriteria> SearchEngine::getSearchHistory() const
{
    return m_searchHistory;
}

QStringList SearchEngine::getSearchSuggestions(const QString &partial) const
{
    Q_UNUSED(partial)
    return QStringList();
}

void SearchEngine::clearSearchHistory()
{
    m_searchHistory.clear();
}

void SearchEngine::buildIndex(const QString &basePath)
{
    Q_UNUSED(basePath)
    // TODO: Implement index building
}

void SearchEngine::updateIndex(const QString &path)
{
    Q_UNUSED(path)
    // TODO: Implement index updating
}

void SearchEngine::removeFromIndex(const QString &path)
{
    Q_UNUSED(path)
    // TODO: Implement index removal
}

void SearchEngine::clearIndex()
{
    m_fileIndex.clear();
    m_contentIndex.clear();
    m_metadataIndex.clear();
    m_indexBuilt = false;
}

bool SearchEngine::isIndexBuilt() const
{
    return m_indexBuilt;
}

#include "SearchEngine.moc" 