#include "FileIndexer.h"
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QStandardPaths>
#include <QMutexLocker>
#include <QtConcurrent>

FileIndexer::FileIndexer(QObject *parent)
    : QObject(parent)
    , m_indexingThread(nullptr)
    , m_saveTimer(nullptr)
    , m_isIndexing(0)
    , m_isPaused(0)
    , m_totalFiles(0)
    , m_processedFiles(0)
{
    m_saveTimer = new QTimer(this);
    m_saveTimer->setInterval(30000); // Save every 30 seconds
    m_saveTimer->setSingleShot(false);
    connect(m_saveTimer, &QTimer::timeout, this, &FileIndexer::saveIndex);
}

FileIndexer::~FileIndexer()
{
    stopIndexing();
    saveIndex();
}

void FileIndexer::startIndexing(const QString &basePath)
{
    if (m_isIndexing.loadAcquire()) {
        return;
    }
    
    m_basePath = basePath.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::HomeLocation) : basePath;
    m_isIndexing.storeRelease(1);
    m_isPaused.storeRelease(0);
    m_processedFiles = 0;
    m_totalFiles = 0;
    
    emit indexingStarted();
    
    // Start indexing in background thread
    QFuture<void> future = QtConcurrent::run([this]() {
        indexDirectory(m_basePath);
        m_isIndexing.storeRelease(0);
        emit indexingCompleted();
    });
    
    m_saveTimer->start();
}

void FileIndexer::stopIndexing()
{
    if (!m_isIndexing.loadAcquire()) {
        return;
    }
    
    m_isIndexing.storeRelease(0);
    m_saveTimer->stop();
    emit indexingStopped();
}

void FileIndexer::pauseIndexing()
{
    if (!m_isIndexing.loadAcquire()) {
        return;
    }
    
    m_isPaused.storeRelease(1);
    emit indexingPaused();
}

void FileIndexer::resumeIndexing()
{
    if (!m_isIndexing.loadAcquire()) {
        return;
    }
    
    m_isPaused.storeRelease(0);
    emit indexingResumed();
}

bool FileIndexer::isIndexing() const
{
    return m_isIndexing.loadAcquire();
}

void FileIndexer::updateIndex(const QString &path)
{
    QMutexLocker locker(&m_indexMutex);
    
    QFileInfo fileInfo(path);
    if (fileInfo.exists() && fileInfo.isFile()) {
        IndexedFile indexedFile = createIndexedFile(path);
        m_fileIndex[path] = indexedFile;
        m_indexedPaths.insert(path);
        emit fileIndexed(indexedFile);
    }
}

void FileIndexer::removeFromIndex(const QString &path)
{
    QMutexLocker locker(&m_indexMutex);
    
    m_fileIndex.remove(path);
    m_indexedPaths.remove(path);
}

void FileIndexer::clearIndex()
{
    QMutexLocker locker(&m_indexMutex);
    
    m_fileIndex.clear();
    m_indexedPaths.clear();
}

QList<FileIndexer::IndexedFile> FileIndexer::searchIndex(const QString &query) const
{
    QMutexLocker locker(const_cast<QMutex*>(&m_indexMutex));
    
    QList<IndexedFile> results;
    QString lowerQuery = query.toLower();
    
    for (auto it = m_fileIndex.constBegin(); it != m_fileIndex.constEnd(); ++it) {
        const IndexedFile &file = it.value();
        
        if (file.name.toLower().contains(lowerQuery) || 
            file.path.toLower().contains(lowerQuery) ||
            file.extension.toLower().contains(lowerQuery)) {
            results.append(file);
        }
        
        if (results.size() >= 1000) { // Limit results
            break;
        }
    }
    
    return results;
}

FileIndexer::IndexedFile FileIndexer::getIndexedFile(const QString &path) const
{
    QMutexLocker locker(const_cast<QMutex*>(&m_indexMutex));
    
    return m_fileIndex.value(path);
}

bool FileIndexer::isFileIndexed(const QString &path) const
{
    QMutexLocker locker(const_cast<QMutex*>(&m_indexMutex));
    
    return m_fileIndex.contains(path);
}

int FileIndexer::getIndexedFileCount() const
{
    QMutexLocker locker(const_cast<QMutex*>(&m_indexMutex));
    
    return m_fileIndex.size();
}

QStringList FileIndexer::getIndexedPaths() const
{
    QMutexLocker locker(const_cast<QMutex*>(&m_indexMutex));
    
    return QStringList(m_indexedPaths.begin(), m_indexedPaths.end());
}

void FileIndexer::indexDirectory(const QString &path)
{
    if (!m_isIndexing.loadAcquire()) {
        return;
    }
    
    // First pass: count files for progress
    QDirIterator countIterator(path, QDir::Files, QDirIterator::Subdirectories);
    while (countIterator.hasNext() && m_isIndexing.loadAcquire()) {
        countIterator.next();
        m_totalFiles++;
    }
    
    // Second pass: index files
    QDirIterator iterator(path, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext() && m_isIndexing.loadAcquire()) {
        // Check if paused
        while (m_isPaused.loadAcquire() && m_isIndexing.loadAcquire()) {
            QThread::msleep(100);
        }
        
        if (!m_isIndexing.loadAcquire()) {
            break;
        }
        
        QString filePath = iterator.next();
        indexFile(filePath);
        
        m_processedFiles++;
        
        // Emit progress every 100 files
        if (m_processedFiles % 100 == 0) {
            int progress = m_totalFiles > 0 ? (m_processedFiles * 100) / m_totalFiles : 0;
            emit indexingProgress(progress);
        }
    }
    
    // Final progress update
    if (m_isIndexing.loadAcquire()) {
        emit indexingProgress(100);
    }
}

void FileIndexer::indexFile(const QString &path)
{
    QMutexLocker locker(&m_indexMutex);
    
    try {
        IndexedFile indexedFile = createIndexedFile(path);
        m_fileIndex[path] = indexedFile;
        m_indexedPaths.insert(path);
        
        emit fileIndexed(indexedFile);
    } catch (const std::exception &e) {
        qWarning() << "Error indexing file" << path << ":" << e.what();
        emit indexingError(QString("Error indexing file %1: %2").arg(path).arg(e.what()));
    }
}

FileIndexer::IndexedFile FileIndexer::createIndexedFile(const QString &path)
{
    IndexedFile file;
    
    QFileInfo fileInfo(path);
    file.path = path;
    file.name = fileInfo.fileName();
    file.extension = fileInfo.suffix().toLower();
    file.size = fileInfo.size();
    file.lastModified = fileInfo.lastModified();
    file.lastAccessed = fileInfo.lastRead();
    file.created = fileInfo.birthTime();
    
    // Get MIME type
    QMimeDatabase mimeDatabase;
    QMimeType mimeType = mimeDatabase.mimeTypeForFile(path);
    file.mimeType = mimeType.name();
    
    // TODO: Extract tags and comments from extended attributes
    // This would require macOS-specific code
    
    return file;
}

void FileIndexer::saveIndex()
{
    QMutexLocker locker(&m_indexMutex);
    
    // TODO: Implement index persistence
    // For now, just emit a signal
    qDebug() << "Saving index with" << m_fileIndex.size() << "files";
}

void FileIndexer::loadIndex()
{
    QMutexLocker locker(&m_indexMutex);
    
    // TODO: Implement index loading
    // For now, just emit a signal
    qDebug() << "Loading index";
}

void FileIndexer::onIndexingFinished()
{
    m_isIndexing.storeRelease(0);
    m_saveTimer->stop();
    saveIndex();
    emit indexingCompleted();
}

#include "FileIndexer.moc" 