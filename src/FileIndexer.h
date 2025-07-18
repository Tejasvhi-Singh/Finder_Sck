#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QHash>
#include <QSet>
#include <QFileInfo>
#include <QDateTime>
#include <QStringList>
#include <QAtomicInt>

class FileIndexer : public QObject
{
    Q_OBJECT

public:
    struct IndexedFile {
        QString path;
        QString name;
        QString extension;
        QString mimeType;
        qint64 size;
        QDateTime lastModified;
        QDateTime lastAccessed;
        QDateTime created;
        QStringList tags;
        QString comment;
        QHash<QString, QVariant> metadata;
    };

    explicit FileIndexer(QObject *parent = nullptr);
    ~FileIndexer();

    void startIndexing(const QString &basePath = QString());
    void stopIndexing();
    void pauseIndexing();
    void resumeIndexing();
    bool isIndexing() const;

    void updateIndex(const QString &path);
    void removeFromIndex(const QString &path);
    void clearIndex();
    
    QList<IndexedFile> searchIndex(const QString &query) const;
    IndexedFile getIndexedFile(const QString &path) const;
    bool isFileIndexed(const QString &path) const;
    
    int getIndexedFileCount() const;
    QStringList getIndexedPaths() const;

signals:
    void indexingStarted();
    void indexingProgress(int percentage);
    void indexingCompleted();
    void indexingPaused();
    void indexingResumed();
    void indexingStopped();
    void indexingError(const QString &error);
    void fileIndexed(const IndexedFile &file);

private slots:
    void onIndexingFinished();

private:
    void indexDirectory(const QString &path);
    void indexFile(const QString &path);
    IndexedFile createIndexedFile(const QString &path);
    void saveIndex();
    void loadIndex();

    QThread *m_indexingThread;
    QTimer *m_saveTimer;
    QMutex m_indexMutex;
    
    QHash<QString, IndexedFile> m_fileIndex;
    QSet<QString> m_indexedPaths;
    QAtomicInt m_isIndexing;
    QAtomicInt m_isPaused;
    
    QString m_basePath;
    int m_totalFiles;
    int m_processedFiles;
}; 