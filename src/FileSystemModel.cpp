#include "FileSystemModel.h"
#include <QDir>
#include <QMimeType>
#include <QMimeData>
#include <QUrl>
#include <QPixmap>
#include <QApplication>
#include <QStyle>
#include <QFileIconProvider>
#include <QDebug>

FileSystemModel::FileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
    , m_showHidden(false)
    , m_showSystemFiles(false)
    , m_thumbnailsEnabled(true)
    , m_cacheSize(DEFAULT_CACHE_SIZE)
{
    initializeModel();
}

FileSystemModel::~FileSystemModel()
{
    clearCache();
}

void FileSystemModel::initializeModel()
{
    // Set up basic model
    setRootPath("");
    setReadOnly(false);
    
    // Set up cache cleanup timer
    m_cacheCleanupTimer = new QTimer(this);
    m_cacheCleanupTimer->setInterval(CACHE_CLEANUP_INTERVAL);
    connect(m_cacheCleanupTimer, &QTimer::timeout, this, &FileSystemModel::clearCache);
    m_cacheCleanupTimer->start();
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    QString filePath = this->filePath(index);
    
    switch (role) {
    case FilePermissionsRole:
        return getFilePermissions(filePath);
    case FileOwnerRole:
        return getFileOwner(filePath);
    case FileGroupRole:
        return getFileGroup(filePath);
    case FileCreationTimeRole:
        return getFileCreationTime(filePath);
    case FileAccessTimeRole:
        return getFileAccessTime(filePath);
    case FileHiddenRole:
        return isHiddenFile(filePath);
    case FileSymlinkRole:
        return QFileInfo(filePath).isSymLink();
    case FileExecutableRole:
        return QFileInfo(filePath).isExecutable();
    case FileMimeTypeRole:
        return getFileMimeType(filePath);
    case FileIconRole:
        return getFileIcon(filePath);
    case FileTagsRole:
        return getFileTags(filePath);
    case FileCommentRole:
        return getFileComment(filePath);
    default:
        return QFileSystemModel::data(index, role);
    }
}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QFileSystemModel::flags(index);
    
    if (index.isValid()) {
        flags |= Qt::ItemIsDragEnabled;
        if (isDir(index)) {
            flags |= Qt::ItemIsDropEnabled;
        }
    }
    
    return flags;
}

QStringList FileSystemModel::mimeTypes() const
{
    return QStringList() << "text/uri-list";
}

QMimeData *FileSystemModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QList<QUrl> urls;
    
    for (const QModelIndex &index : indexes) {
        if (index.isValid()) {
            urls << QUrl::fromLocalFile(filePath(index));
        }
    }
    
    mimeData->setUrls(urls);
    return mimeData;
}

bool FileSystemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    
    if (!data->hasUrls()) {
        return false;
    }
    
    QString targetPath = filePath(parent);
    if (!QFileInfo(targetPath).isDir()) {
        return false;
    }
    
    QList<QUrl> urls = data->urls();
    for (const QUrl &url : urls) {
        if (url.isLocalFile()) {
            QString sourcePath = url.toLocalFile();
            QString fileName = QFileInfo(sourcePath).fileName();
            QString destPath = targetPath + "/" + fileName;
            
            if (action == Qt::MoveAction) {
                moveFile(sourcePath, destPath);
            } else if (action == Qt::CopyAction) {
                copyFile(sourcePath, destPath);
            }
        }
    }
    
    return true;
}

Qt::DropActions FileSystemModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

Qt::DropActions FileSystemModel::supportedDragActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

void FileSystemModel::setShowHidden(bool show)
{
    if (m_showHidden != show) {
        m_showHidden = show;
        if (show) {
            setFilter(filter() | QDir::Hidden);
        } else {
            setFilter(filter() & ~QDir::Hidden);
        }
    }
}

bool FileSystemModel::showHidden() const
{
    return m_showHidden;
}

void FileSystemModel::setShowSystemFiles(bool show)
{
    if (m_showSystemFiles != show) {
        m_showSystemFiles = show;
        if (show) {
            setFilter(filter() | QDir::System);
        } else {
            setFilter(filter() & ~QDir::System);
        }
    }
}

bool FileSystemModel::showSystemFiles() const
{
    return m_showSystemFiles;
}

void FileSystemModel::refresh()
{
    clearCache();
    // QFileSystemModel doesn't have a refresh method, so we'll trigger a refresh differently
    beginResetModel();
    endResetModel();
}

void FileSystemModel::refreshIndex(const QModelIndex &index)
{
    if (index.isValid()) {
        QString path = filePath(index);
        m_metadataCache.remove(path);
        m_thumbnailCache.remove(path);
        m_iconCache.remove(path);
        emit dataChanged(index, index);
    }
}

QString FileSystemModel::getFilePermissions(const QString &path) const
{
    QFileInfo info(path);
    QString permissions;
    
    // Owner permissions
    permissions += (info.permission(QFile::ReadOwner) ? "r" : "-");
    permissions += (info.permission(QFile::WriteOwner) ? "w" : "-");
    permissions += (info.permission(QFile::ExeOwner) ? "x" : "-");
    
    // Group permissions
    permissions += (info.permission(QFile::ReadGroup) ? "r" : "-");
    permissions += (info.permission(QFile::WriteGroup) ? "w" : "-");
    permissions += (info.permission(QFile::ExeGroup) ? "x" : "-");
    
    // Other permissions
    permissions += (info.permission(QFile::ReadOther) ? "r" : "-");
    permissions += (info.permission(QFile::WriteOther) ? "w" : "-");
    permissions += (info.permission(QFile::ExeOther) ? "x" : "-");
    
    return permissions;
}

QString FileSystemModel::getFileOwner(const QString &path) const
{
    QFileInfo info(path);
    return info.owner();
}

QString FileSystemModel::getFileGroup(const QString &path) const
{
    QFileInfo info(path);
    return info.group();
}

QDateTime FileSystemModel::getFileCreationTime(const QString &path) const
{
    QFileInfo info(path);
    return info.birthTime();
}

QDateTime FileSystemModel::getFileAccessTime(const QString &path) const
{
    QFileInfo info(path);
    return info.lastRead();
}

QString FileSystemModel::getFileMimeType(const QString &path) const
{
    QMimeType mimeType = m_mimeDatabase.mimeTypeForFile(path);
    return mimeType.name();
}

QIcon FileSystemModel::getFileIcon(const QString &path) const
{
    QMutexLocker locker(&m_cacheMutex);
    
    if (m_iconCache.contains(path)) {
        return m_iconCache[path];
    }
    
    QIcon icon = generateFileIcon(path);
    m_iconCache[path] = icon;
    
    return icon;
}

QStringList FileSystemModel::getFileTags(const QString &path) const
{
    Q_UNUSED(path)
    // This would integrate with macOS extended attributes
    return QStringList();
}

QString FileSystemModel::getFileComment(const QString &path) const
{
    Q_UNUSED(path)
    // This would integrate with macOS extended attributes
    return QString();
}

void FileSystemModel::enableThumbnails(bool enable)
{
    m_thumbnailsEnabled = enable;
    if (!enable) {
        m_thumbnailCache.clear();
    }
}

bool FileSystemModel::thumbnailsEnabled() const
{
    return m_thumbnailsEnabled;
}

QPixmap FileSystemModel::getThumbnail(const QString &path, const QSize &size) const
{
    QMutexLocker locker(&m_cacheMutex);
    
    QString key = path + QString("_%1x%2").arg(size.width()).arg(size.height());
    if (m_thumbnailCache.contains(key)) {
        return m_thumbnailCache[key];
    }
    
    QPixmap thumbnail = generateThumbnail(path, size);
    m_thumbnailCache[key] = thumbnail;
    
    return thumbnail;
}

void FileSystemModel::setCacheSize(int size)
{
    m_cacheSize = size;
    // Clear cache if it exceeds new size
    if (m_metadataCache.size() > size) {
        clearCache();
    }
}

int FileSystemModel::cacheSize() const
{
    return m_cacheSize;
}

void FileSystemModel::clearCache()
{
    QMutexLocker locker(&m_cacheMutex);
    m_metadataCache.clear();
    m_thumbnailCache.clear();
    m_iconCache.clear();
}

bool FileSystemModel::createDirectory(const QString &path, const QString &name)
{
    QDir dir(path);
    bool success = dir.mkdir(name);
    if (success) {
        emit fileOperationCompleted("createDirectory", true, QString());
    } else {
        emit fileOperationCompleted("createDirectory", false, "Failed to create directory");
    }
    return success;
}

bool FileSystemModel::removeFile(const QString &path)
{
    QFileInfo info(path);
    bool success = false;
    
    if (info.isDir()) {
        QDir dir(path);
        success = dir.removeRecursively();
    } else {
        success = QFile::remove(path);
    }
    
    if (success) {
        emit fileOperationCompleted("removeFile", true, QString());
    } else {
        emit fileOperationCompleted("removeFile", false, "Failed to remove file");
    }
    return success;
}

bool FileSystemModel::renameFile(const QString &oldPath, const QString &newPath)
{
    bool success = QFile::rename(oldPath, newPath);
    if (success) {
        emit fileOperationCompleted("renameFile", true, QString());
    } else {
        emit fileOperationCompleted("renameFile", false, "Failed to rename file");
    }
    return success;
}

bool FileSystemModel::copyFile(const QString &sourcePath, const QString &destPath)
{
    bool success = QFile::copy(sourcePath, destPath);
    if (success) {
        emit fileOperationCompleted("copyFile", true, QString());
    } else {
        emit fileOperationCompleted("copyFile", false, "Failed to copy file");
    }
    return success;
}

bool FileSystemModel::moveFile(const QString &sourcePath, const QString &destPath)
{
    bool success = QFile::rename(sourcePath, destPath);
    if (success) {
        emit fileOperationCompleted("moveFile", true, QString());
    } else {
        emit fileOperationCompleted("moveFile", false, "Failed to move file");
    }
    return success;
}

QIcon FileSystemModel::generateFileIcon(const QString &path) const
{
    QFileIconProvider iconProvider;
    QFileInfo info(path);
    return iconProvider.icon(info);
}

QPixmap FileSystemModel::generateThumbnail(const QString &path, const QSize &size) const
{
    QFileInfo info(path);
    
    // For images, load and scale
    if (info.suffix().toLower() == "png" || info.suffix().toLower() == "jpg" || 
        info.suffix().toLower() == "jpeg" || info.suffix().toLower() == "gif" ||
        info.suffix().toLower() == "bmp" || info.suffix().toLower() == "tiff") {
        
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            return pixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
    
    // For other files, use file icon
    QIcon icon = generateFileIcon(path);
    return icon.pixmap(size);
}

bool FileSystemModel::isHiddenFile(const QString &path) const
{
    QFileInfo info(path);
    return info.isHidden() || info.fileName().startsWith('.');
}

bool FileSystemModel::isSystemFile(const QString &path) const
{
    QFileInfo info(path);
    return info.fileName().startsWith('.') && 
           (info.fileName().contains("DS_Store") || 
            info.fileName().contains("Spotlight") ||
            info.fileName().contains("Trashes"));
}

void FileSystemModel::onDirectoryLoaded()
{
    // Handle directory loading completion
}

void FileSystemModel::onThumbnailGenerated()
{
    // Handle thumbnail generation completion
}

void FileSystemModel::onFileOperationFinished()
{
    // Handle file operation completion
}

#include "FileSystemModel.moc" 