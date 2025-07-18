#pragma once

#include <QObject>
#include <QFileInfo>
#include <QStringList>
#include <QDateTime>
#include <QPixmap>
#include <QIcon>
#include <QUrl>
#include <QProcess>
#include <QTimer>
#include <QMutex>
#include <QHash>
#include <QSet>
#include <memory>

// Forward declarations for Objective-C classes
#ifdef __OBJC__
@class NSString;
@class NSImage;
@class NSWorkspace;
@class NSMetadataQuery;
@class FSEventStreamRef;
#else
// Use Qt's forward declaration to avoid conflicts
Q_FORWARD_DECLARE_OBJC_CLASS(NSString);
Q_FORWARD_DECLARE_OBJC_CLASS(NSImage);
Q_FORWARD_DECLARE_OBJC_CLASS(NSWorkspace);
Q_FORWARD_DECLARE_OBJC_CLASS(NSMetadataQuery);
typedef struct __FSEventStream* FSEventStreamRef;
#endif

class MacOSIntegration : public QObject
{
    Q_OBJECT

public:
    enum FileSystemEvent {
        FileCreated,
        FileModified,
        FileDeleted,
        FileRenamed,
        FileAttributeChanged,
        DirectoryCreated,
        DirectoryDeleted,
        DirectoryRenamed
    };

    enum SpotlightScope {
        CurrentUser,
        LocalComputer,
        NetworkVolumes,
        AllVolumes
    };

    struct FileSystemEventInfo {
        QString path;
        FileSystemEvent event;
        QDateTime timestamp;
        QString oldPath; // For rename events
        QHash<QString, QVariant> metadata;
        
        FileSystemEventInfo() : event(FileCreated) {}
    };

    struct SpotlightResult {
        QString path;
        QString displayName;
        QString contentType;
        QString kind;
        qint64 size;
        QDateTime dateCreated;
        QDateTime dateModified;
        QDateTime dateLastUsed;
        QStringList authors;
        QString comment;
        QStringList keywords;
        double relevanceScore;
        QHash<QString, QVariant> metadata;
        
        SpotlightResult() : size(0), relevanceScore(0.0) {}
    };

    explicit MacOSIntegration(QObject *parent = nullptr);
    ~MacOSIntegration();

    // Spotlight integration
    void enableSpotlightIntegration(bool enable);
    bool isSpotlightEnabled() const;
    
    void searchWithSpotlight(const QString &query, SpotlightScope scope = CurrentUser);
    void searchSpotlightMetadata(const QHash<QString, QVariant> &criteria, SpotlightScope scope = CurrentUser);
    void cancelSpotlightSearch();
    bool isSpotlightSearching() const;
    
    // File system events monitoring
    void startFileSystemMonitoring(const QStringList &paths);
    void stopFileSystemMonitoring();
    bool isFileSystemMonitoringActive() const;
    void addPathToMonitor(const QString &path);
    void removePathFromMonitor(const QString &path);
    
    // Quick Look integration
    void showQuickLookPreview(const QString &filePath);
    void hideQuickLookPreview();
    bool isQuickLookPreviewVisible() const;
    QPixmap getQuickLookThumbnail(const QString &filePath, const QSize &size = QSize(256, 256));
    
    // Finder integration
    void revealInFinder(const QString &filePath);
    void selectInFinder(const QString &filePath);
    void openWithFinder(const QString &filePath);
    void moveToTrash(const QString &filePath);
    void moveToTrash(const QStringList &filePaths);
    
    // File operations with native dialogs
    QString showNativeOpenDialog(const QString &title, const QString &startPath, const QStringList &filters);
    QStringList showNativeOpenMultipleDialog(const QString &title, const QString &startPath, const QStringList &filters);
    QString showNativeSaveDialog(const QString &title, const QString &startPath, const QStringList &filters);
    QString showNativeFolderDialog(const QString &title, const QString &startPath);
    
    // File metadata and extended attributes
    QHash<QString, QVariant> getFileMetadata(const QString &filePath);
    QHash<QString, QVariant> getExtendedAttributes(const QString &filePath);
    bool setExtendedAttribute(const QString &filePath, const QString &key, const QVariant &value);
    bool removeExtendedAttribute(const QString &filePath, const QString &key);
    
    // File tags and comments
    QStringList getFileTags(const QString &filePath);
    bool setFileTags(const QString &filePath, const QStringList &tags);
    QString getFileComment(const QString &filePath);
    bool setFileComment(const QString &filePath, const QString &comment);
    
    // File icons and thumbnails
    QIcon getFileIcon(const QString &filePath, const QSize &size = QSize(32, 32));
    QPixmap getFileThumbnail(const QString &filePath, const QSize &size = QSize(128, 128));
    QIcon getGenericFileIcon(const QString &fileType, const QSize &size = QSize(32, 32));
    
    // System integration
    void openWithDefaultApplication(const QString &filePath);
    void openWithApplication(const QString &filePath, const QString &applicationPath);
    QStringList getAvailableApplications(const QString &filePath);
    QString getDefaultApplication(const QString &filePath);
    
    // Workspace notifications
    void enableWorkspaceNotifications(bool enable);
    bool isWorkspaceNotificationsEnabled() const;
    
    // Security and permissions
    bool requestFullDiskAccess();
    bool hasFullDiskAccess() const;
    QStringList getSecurityScopedPaths();
    
    // Performance optimization
    void enableSpotlightCache(bool enable);
    bool isSpotlightCacheEnabled() const;
    void clearSpotlightCache();
    
    // Utility methods
    bool isFileOnExternalVolume(const QString &filePath);
    bool isFileOnNetworkVolume(const QString &filePath);
    QString getVolumeNameForPath(const QString &filePath);
    QStringList getMountedVolumes();
    
    // Version control integration
    QStringList getVersionControlStatus(const QString &filePath);
    bool isUnderVersionControl(const QString &filePath);

signals:
    void spotlightSearchStarted(const QString &query);
    void spotlightSearchCompleted(const QList<SpotlightResult> &results);
    void spotlightSearchCancelled();
    void spotlightSearchProgress(int percentage);
    void spotlightSearchError(const QString &error);
    
    void fileSystemEventOccurred(const FileSystemEventInfo &event);
    void fileSystemMonitoringStarted();
    void fileSystemMonitoringStopped();
    void fileSystemMonitoringError(const QString &error);
    
    void quickLookPreviewShown(const QString &filePath);
    void quickLookPreviewHidden();
    
    void workspaceNotificationReceived(const QString &type, const QHash<QString, QVariant> &info);
    
    void securityAccessGranted(const QString &path);
    void securityAccessDenied(const QString &path);

private slots:
    void onSpotlightQueryFinished();
    void onFileSystemEventReceived();
    void onWorkspaceNotificationReceived();

private:
    // Objective-C bridge methods
    void initializeNativeComponents();
    void cleanupNativeComponents();
    
    // Spotlight implementation
    void setupSpotlightQuery();
    void startSpotlightQuery(const QString &query, SpotlightScope scope);
    void processSpotlightResults();
    
    // FSEvents implementation
    void setupFileSystemEvents();
    void startFileSystemEvents(const QStringList &paths);
    void stopFileSystemEvents();
    void processFileSystemEvent(const QString &path, uint64_t eventFlags);
    
    // Native file operations
    NSString* qtStringToNSString(const QString &str);
    QString nsStringToQString(NSString *nsStr);
    QPixmap nsImageToQPixmap(NSImage *image);
    
    // Implementation classes
    // class SpotlightSearchManager;
    // class FileSystemEventsManager;
    // class QuickLookManager;
    // class WorkspaceManager;
    
    // Note: Commented out to avoid compilation issues with forward declared classes
    // std::unique_ptr<SpotlightSearchManager> m_spotlightManager;
    // std::unique_ptr<FileSystemEventsManager> m_fsEventsManager;
    // std::unique_ptr<QuickLookManager> m_quickLookManager;
    // std::unique_ptr<WorkspaceManager> m_workspaceManager;
    
    // Native objects
    NSWorkspace *m_workspace;
    NSMetadataQuery *m_metadataQuery;
    FSEventStreamRef m_fsEventStream;
    
    // State management
    bool m_spotlightEnabled;
    bool m_fileSystemMonitoringActive;
    bool m_workspaceNotificationsEnabled;
    bool m_spotlightCacheEnabled;
    
    // Monitored paths
    QStringList m_monitoredPaths;
    QMutex m_pathsMutex;
    
    // Cache
    QHash<QString, QHash<QString, QVariant>> m_metadataCache;
    QHash<QString, QPixmap> m_thumbnailCache;
    QHash<QString, QIcon> m_iconCache;
    QTimer *m_cacheCleanupTimer;
    
    // Performance monitoring
    QTimer *m_performanceTimer;
    int m_spotlightSearchCount;
    int m_fileSystemEventCount;
    
    // Security
    QSet<QString> m_securityScopedPaths;
    
    static const int CACHE_CLEANUP_INTERVAL = 600000; // 10 minutes
    static const int PERFORMANCE_MONITOR_INTERVAL = 60000; // 1 minute
}; 