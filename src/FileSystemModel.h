#pragma once

#include <QAbstractItemModel>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QIcon>
#include <QMimeDatabase>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <QHash>
#include <QDateTime>
#include <QFuture>
#include <QFutureWatcher>
#include <memory>

class FileSystemModel : public QFileSystemModel
{
    Q_OBJECT

public:
    enum CustomRoles {
        FilePermissionsRole = Qt::UserRole + 1,
        FileOwnerRole,
        FileGroupRole,
        FileCreationTimeRole,
        FileAccessTimeRole,
        FileHiddenRole,
        FileSymlinkRole,
        FileExecutableRole,
        FileMimeTypeRole,
        FileIconRole,
        FilePreviewRole,
        FileTagsRole,
        FileCommentRole
    };

    explicit FileSystemModel(QObject *parent = nullptr);
    ~FileSystemModel();

    // Enhanced QFileSystemModel interface
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    Qt::DropActions supportedDropActions() const override;
    Qt::DropActions supportedDragActions() const override;

    // Custom methods
    void setShowHidden(bool show);
    bool showHidden() const;
    
    void setShowSystemFiles(bool show);
    bool showSystemFiles() const;
    
    void refresh();
    void refreshIndex(const QModelIndex &index);
    
    // File operations
    bool createDirectory(const QString &path, const QString &name);
    bool removeFile(const QString &path);
    bool renameFile(const QString &oldPath, const QString &newPath);
    bool copyFile(const QString &sourcePath, const QString &destPath);
    bool moveFile(const QString &sourcePath, const QString &destPath);
    
    // Advanced file info
    QString getFilePermissions(const QString &path) const;
    QString getFileOwner(const QString &path) const;
    QString getFileGroup(const QString &path) const;
    QDateTime getFileCreationTime(const QString &path) const;
    QDateTime getFileAccessTime(const QString &path) const;
    QString getFileMimeType(const QString &path) const;
    QIcon getFileIcon(const QString &path) const;
    QStringList getFileTags(const QString &path) const;
    QString getFileComment(const QString &path) const;
    
    // Thumbnail and preview support
    void enableThumbnails(bool enable);
    bool thumbnailsEnabled() const;
    QPixmap getThumbnail(const QString &path, const QSize &size = QSize(128, 128)) const;
    
    // Performance optimization
    void setCacheSize(int size);
    int cacheSize() const;
    void clearCache();
    
    // Async operations
    void loadDirectoryAsync(const QString &path);
    void generateThumbnailAsync(const QString &path, const QSize &size);

signals:
    void directoryLoaded(const QString &path);
    void thumbnailGenerated(const QString &path, const QPixmap &thumbnail);
    void fileOperationCompleted(const QString &operation, bool success, const QString &error);
    void indexingProgress(int progress);
    void indexingCompleted();

private slots:
    void onDirectoryLoaded();
    void onThumbnailGenerated();
    void onFileOperationFinished();

private:
    void initializeModel();
    void setupCache();
    void setupThumbnailGeneration();
    void loadFileMetadata(const QString &path);
    QIcon generateFileIcon(const QString &path) const;
    QPixmap generateThumbnail(const QString &path, const QSize &size) const;
    bool isHiddenFile(const QString &path) const;
    bool isSystemFile(const QString &path) const;
    
    // Threading for async operations
    // class AsyncLoader;
    // class ThumbnailGenerator;
    
    // Note: Commented out to avoid compilation issues with forward declared classes
    // std::unique_ptr<AsyncLoader> m_asyncLoader;
    // std::unique_ptr<ThumbnailGenerator> m_thumbnailGenerator;
    
    // Cache for metadata and thumbnails
    mutable QHash<QString, QVariant> m_metadataCache;
    mutable QHash<QString, QPixmap> m_thumbnailCache;
    mutable QHash<QString, QIcon> m_iconCache;
    mutable QMutex m_cacheMutex;
    
    // Settings
    bool m_showHidden;
    bool m_showSystemFiles;
    bool m_thumbnailsEnabled;
    int m_cacheSize;
    
    // Mime database for file type detection
    QMimeDatabase m_mimeDatabase;
    
    // Async operation management
    QFutureWatcher<void> m_directoryWatcher;
    QFutureWatcher<QPixmap> m_thumbnailWatcher;
    
    // Performance monitoring
    QTimer *m_cacheCleanupTimer;
    static const int CACHE_CLEANUP_INTERVAL = 300000; // 5 minutes
    static const int DEFAULT_CACHE_SIZE = 1000;
}; 