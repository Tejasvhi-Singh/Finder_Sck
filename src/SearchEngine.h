#pragma once

#include <QObject>
#include <QFileInfo>
#include <QDateTime>
#include <QRegularExpression>
#include <QMimeDatabase>
#include <QStringList>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QFuture>
#include <QFutureWatcher>
#include <QTimer>
#include <QElapsedTimer>
#include <QHash>
#include <QSet>
#include <QAtomicInt>
#include <QQueue>
#include <memory>

class SearchEngine : public QObject
{
    Q_OBJECT

public:
    enum SearchType {
        FileNameSearch,
        ContentSearch,
        MetadataSearch,
        AdvancedSearch,
        FuzzySearch,
        RegexSearch,
        DateSearch,
        SizeSearch,
        TypeSearch
    };

    enum SearchScope {
        CurrentDirectory,
        CurrentDirectoryRecursive,
        HomeDirectory,
        EntireSystem,
        CustomPath
    };

    struct SearchCriteria {
        QString query;
        SearchType type;
        SearchScope scope;
        QString customPath;
        
        // Advanced filters
        QStringList fileTypes;
        QStringList excludePatterns;
        qint64 minSize;
        qint64 maxSize;
        QDateTime dateFrom;
        QDateTime dateTo;
        
        // Search options
        bool caseSensitive;
        bool wholeWords;
        bool useRegex;
        bool includeBinaryFiles;
        bool followSymlinks;
        bool searchHiddenFiles;
        bool searchSystemFiles;
        bool fuzzyMatching;
        
        // Filter options
        bool useSizeFilter;
        bool useDateFilter;
        bool searchSubfolders;
        
        // Performance options
        int maxResults;
        int maxDepth;
        int timeoutMs;
        
        SearchCriteria() : 
            type(FileNameSearch), 
            scope(CurrentDirectory),
            minSize(0), 
            maxSize(0),
            caseSensitive(false),
            wholeWords(false),
            useRegex(false),
            includeBinaryFiles(false),
            followSymlinks(false),
            searchHiddenFiles(false),
            searchSystemFiles(false),
            fuzzyMatching(false),
            useSizeFilter(false),
            useDateFilter(false),
            searchSubfolders(true),
            maxResults(10000),
            maxDepth(100),
            timeoutMs(30000)
        {}
    };

    struct SearchResult {
        QString filePath;
        QString fileName;
        QString directory;
        QFileInfo fileInfo;
        QString mimeType;
        double relevanceScore;
        QStringList matchedLines;
        QList<int> matchPositions;
        QString preview;
        QDateTime lastModified;
        qint64 fileSize;
        
        SearchResult() : relevanceScore(0.0), fileSize(0) {}
    };

    explicit SearchEngine(QObject *parent = nullptr);
    ~SearchEngine();

    // Main search interface
    void search(const QString &query, const QString &basePath = QString());
    void search(const SearchCriteria &criteria);
    void cancelSearch();
    bool isSearching() const;
    
    // Advanced search methods
    void searchByName(const QString &pattern, const QString &basePath);
    void searchByContent(const QString &text, const QString &basePath);
    void searchByMetadata(const QHash<QString, QVariant> &metadata, const QString &basePath);
    void searchByRegex(const QRegularExpression &regex, const QString &basePath);
    void fuzzySearch(const QString &query, const QString &basePath);
    void searchByDateRange(const QDateTime &from, const QDateTime &to, const QString &basePath);
    void searchBySizeRange(qint64 minSize, qint64 maxSize, const QString &basePath);
    void searchByType(const QStringList &mimeTypes, const QString &basePath);
    
    // Search history and suggestions
    void saveSearch(const SearchCriteria &criteria);
    QList<SearchCriteria> getSearchHistory() const;
    QStringList getSearchSuggestions(const QString &partial) const;
    void clearSearchHistory();
    
    // Configuration
    void setMaxResults(int maxResults);
    int maxResults() const;
    
    void setMaxDepth(int maxDepth);
    int maxDepth() const;
    
    void setTimeout(int timeoutMs);
    int timeout() const;
    
    void setThreadCount(int threadCount);
    int threadCount() const;
    
    // Index management
    void buildIndex(const QString &basePath);
    void updateIndex(const QString &path);
    void removeFromIndex(const QString &path);
    void clearIndex();
    bool isIndexBuilt() const;
    
    // Performance monitoring
    int getLastSearchTime() const;
    int getResultCount() const;
    QString getSearchStatistics() const;

signals:
    void searchStarted(const QString &query);
    void searchCompleted(const QList<SearchResult> &results);
    void searchCancelled();
    void searchProgress(int percentage);
    void searchError(const QString &error);
    void indexingProgress(int percentage);
    void indexingCompleted();
    void resultFound(const SearchResult &result);

private slots:
    void onSearchFinished();
    void onIndexingFinished();
    void onSearchWorkerFinished();

private:
    // Search implementation
    class SearchWorker;
    class IndexBuilder;
    class FuzzyMatcher;
    class ContentSearcher;
    class MetadataSearcher;
    
    void performSearch(const SearchCriteria &criteria);
    void searchInDirectory(const QString &path, const SearchCriteria &criteria, QList<SearchResult> &results);
    void searchInFile(const QString &filePath, const SearchCriteria &criteria, QList<SearchResult> &results);
    
    // Specific search implementations
    bool matchesFileName(const QString &fileName, const SearchCriteria &criteria);
    bool matchesContent(const QString &filePath, const SearchCriteria &criteria, QStringList &matchedLines);
    bool matchesMetadata(const QFileInfo &fileInfo, const SearchCriteria &criteria);
    bool matchesFilters(const QFileInfo &fileInfo, const SearchCriteria &criteria);
    
    // Fuzzy matching
    double calculateFuzzyScore(const QString &query, const QString &target);
    bool fuzzyMatch(const QString &query, const QString &target, double threshold = 0.6);
    
    // Content analysis
    bool isBinaryFile(const QString &filePath);
    QString extractTextContent(const QString &filePath);
    QStringList extractMetadata(const QString &filePath);
    
    // Scoring and ranking
    double calculateRelevanceScore(const SearchResult &result, const SearchCriteria &criteria);
    void rankResults(QList<SearchResult> &results, const SearchCriteria &criteria);
    
    // Index management
    void buildFileIndex(const QString &basePath);
    void updateFileIndex(const QString &filePath);
    void loadIndex();
    void saveIndex();
    
    // Threading and performance
    // Note: Using raw pointers for forward declared classes to avoid compilation issues
    // std::unique_ptr<SearchWorker> m_searchWorker;
    // std::unique_ptr<IndexBuilder> m_indexBuilder;
    // std::unique_ptr<FuzzyMatcher> m_fuzzyMatcher;
    // std::unique_ptr<ContentSearcher> m_contentSearcher;
    // std::unique_ptr<MetadataSearcher> m_metadataSearcher;
    
    QThread *m_searchThread;
    QThread *m_indexThread;
    QFutureWatcher<void> m_searchWatcher;
    QFutureWatcher<void> m_indexWatcher;
    
    // Search state
    QAtomicInt m_isSearching;
    QAtomicInt m_searchCancelled;
    QMutex m_searchMutex;
    QWaitCondition m_searchCondition;
    
    // Configuration
    int m_maxResults;
    int m_maxDepth;
    int m_timeoutMs;
    int m_threadCount;
    
    // Index data
    QHash<QString, QFileInfo> m_fileIndex;
    QHash<QString, QStringList> m_contentIndex;
    QHash<QString, QHash<QString, QVariant>> m_metadataIndex;
    QMutex m_indexMutex;
    bool m_indexBuilt;
    
    // Search history
    QList<SearchCriteria> m_searchHistory;
    QStringList m_searchSuggestions;
    static const int MAX_SEARCH_HISTORY = 100;
    
    // Performance monitoring
    QTimer *m_searchTimer;
    QElapsedTimer *m_elapsedTimer;
    int m_lastSearchTime;
    int m_resultCount;
    
    // MIME database
    QMimeDatabase m_mimeDatabase;
    
    // Common file extensions for optimization
    QHash<QString, QStringList> m_fileTypeExtensions;
    
    // Stop words for content search
    QSet<QString> m_stopWords;
}; 