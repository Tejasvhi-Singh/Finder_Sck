#include "PreviewWidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QImageReader>
#include <QPixmap>
#include <QTextStream>
#include <QStringConverter>
#include <QMutexLocker>
#include <QDebug>

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(nullptr)
    , m_imageLabel(nullptr)
    , m_textEdit(nullptr)
    , m_scrollArea(nullptr)
    , m_infoLabel(nullptr)
    , m_loadTimer(nullptr)
{
    setupUI();
    
    m_loadTimer = new QTimer(this);
    m_loadTimer->setSingleShot(true);
    m_loadTimer->setInterval(100);
    connect(m_loadTimer, &QTimer::timeout, this, &PreviewWidget::onPreviewLoaded);
}

PreviewWidget::~PreviewWidget()
{
    clearPreview();
}

void PreviewWidget::setupUI()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(10);
    
    // Create scroll area for images
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setAlignment(Qt::AlignCenter);
    m_scrollArea->setVisible(false);
    
    // Create image label
    m_imageLabel = new QLabel(this);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setScaledContents(false);
    m_imageLabel->setStyleSheet("QLabel { border: 1px solid #555; background-color: #1a1a1a; }");
    m_scrollArea->setWidget(m_imageLabel);
    
    // Create text edit for text files
    m_textEdit = new QTextEdit(this);
    m_textEdit->setReadOnly(true);
    m_textEdit->setVisible(false);
    m_textEdit->setStyleSheet("QTextEdit { border: 1px solid #555; background-color: #1a1a1a; color: white; }");
    
    // Create info label
    m_infoLabel = new QLabel(this);
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_infoLabel->setStyleSheet("QLabel { color: #ccc; font-size: 12px; }");
    
    // Add widgets to layout
    m_layout->addWidget(m_scrollArea, 1);
    m_layout->addWidget(m_textEdit, 1);
    m_layout->addWidget(m_infoLabel, 0);
    
    // Initially show info label
    showFileInfo("");
}

void PreviewWidget::setFile(const QString &filePath)
{
    if (m_currentFile == filePath) {
        return;
    }
    
    clearPreview();
    m_currentFile = filePath;
    
    if (filePath.isEmpty()) {
        showFileInfo("");
        return;
    }
    
    // Delay loading to avoid excessive updates
    m_loadTimer->start();
}

void PreviewWidget::clearPreview()
{
    m_scrollArea->setVisible(false);
    m_textEdit->setVisible(false);
    m_textEdit->clear();
    m_imageLabel->clear();
    m_imageLabel->setText("");
    m_currentFile.clear();
    
    // Clear caches if they get too large
    if (m_imageCache.size() > 50) {
        m_imageCache.clear();
    }
    if (m_textCache.size() > 50) {
        m_textCache.clear();
    }
}

bool PreviewWidget::isPreviewSupported(const QString &filePath) const
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        return false;
    }
    
    QString suffix = fileInfo.suffix().toLower();
    
    // Image formats
    QStringList imageFormats = {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg", "webp"};
    if (imageFormats.contains(suffix)) {
        return true;
    }
    
    // Text formats
    QStringList textFormats = {"txt", "log", "cpp", "h", "hpp", "c", "cc", "cxx", "py", "js", "html", "htm", "css", "json", "xml", "md", "yaml", "yml"};
    if (textFormats.contains(suffix)) {
        return true;
    }
    
    return false;
}

void PreviewWidget::onPreviewLoaded()
{
    if (m_currentFile.isEmpty()) {
        return;
    }
    
    loadPreview(m_currentFile);
}

void PreviewWidget::loadPreview(const QString &filePath)
{
    QMutexLocker locker(&m_loadMutex);
    
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists() || !fileInfo.isReadable()) {
        showFileInfo(filePath);
        return;
    }
    
    // Always show file info
    showFileInfo(filePath);
    
    QString suffix = fileInfo.suffix().toLower();
    
    // Try to load as image first
    QStringList imageFormats = {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg", "webp"};
    if (imageFormats.contains(suffix)) {
        loadImagePreview(filePath);
        return;
    }
    
    // Try to load as text
    QStringList textFormats = {"txt", "log", "cpp", "h", "hpp", "c", "cc", "cxx", "py", "js", "html", "htm", "css", "json", "xml", "md", "yaml", "yml"};
    if (textFormats.contains(suffix)) {
        loadTextPreview(filePath);
        return;
    }
    
    // For other file types, just show info
    emit previewLoaded(filePath);
}

void PreviewWidget::loadImagePreview(const QString &filePath)
{
    // Check cache first
    if (m_imageCache.contains(filePath)) {
        m_imageLabel->setPixmap(m_imageCache[filePath]);
        m_scrollArea->setVisible(true);
        m_textEdit->setVisible(false);
        emit previewLoaded(filePath);
        return;
    }
    
    QImageReader reader(filePath);
    if (!reader.canRead()) {
        showFileInfo(filePath);
        emit previewError("Cannot read image file");
        return;
    }
    
    // Limit image size for preview
    QSize originalSize = reader.size();
    QSize maxSize(800, 600);
    
    if (originalSize.width() > maxSize.width() || originalSize.height() > maxSize.height()) {
        QSize scaledSize = originalSize.scaled(maxSize, Qt::KeepAspectRatio);
        reader.setScaledSize(scaledSize);
    }
    
    QImage image = reader.read();
    if (image.isNull()) {
        showFileInfo(filePath);
        emit previewError("Failed to load image");
        return;
    }
    
    QPixmap pixmap = QPixmap::fromImage(image);
    m_imageCache[filePath] = pixmap;
    
    m_imageLabel->setPixmap(pixmap);
    m_scrollArea->setVisible(true);
    m_textEdit->setVisible(false);
    
    emit previewLoaded(filePath);
}

void PreviewWidget::loadTextPreview(const QString &filePath)
{
    // Check cache first
    if (m_textCache.contains(filePath)) {
        m_textEdit->setPlainText(m_textCache[filePath]);
        m_textEdit->setVisible(true);
        m_scrollArea->setVisible(false);
        emit previewLoaded(filePath);
        return;
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showFileInfo(filePath);
        emit previewError("Cannot read text file");
        return;
    }
    
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    
    // Limit text size (read max 1MB)
    const qint64 maxSize = 1024 * 1024;
    QString content;
    
    qint64 bytesRead = 0;
    while (!stream.atEnd() && bytesRead < maxSize) {
        QString line = stream.readLine();
        content += line + "\n";
        bytesRead += line.length() + 1;
    }
    
    if (bytesRead >= maxSize) {
        content += "\n\n[File truncated - showing first 1MB]";
    }
    
    file.close();
    
    m_textCache[filePath] = content;
    m_textEdit->setPlainText(content);
    m_textEdit->setVisible(true);
    m_scrollArea->setVisible(false);
    
    emit previewLoaded(filePath);
}

void PreviewWidget::loadVideoPreview(const QString &filePath)
{
    Q_UNUSED(filePath)
    // TODO: Implement video preview (could show first frame or use QuickLook)
    showFileInfo(filePath);
}

void PreviewWidget::loadAudioPreview(const QString &filePath)
{
    Q_UNUSED(filePath)
    // TODO: Implement audio preview (could show waveform or metadata)
    showFileInfo(filePath);
}

void PreviewWidget::loadDocumentPreview(const QString &filePath)
{
    Q_UNUSED(filePath)
    // TODO: Implement document preview (could use QuickLook)
    showFileInfo(filePath);
}

void PreviewWidget::showFileInfo(const QString &filePath)
{
    if (filePath.isEmpty()) {
        m_infoLabel->setText("Select a file to preview");
        return;
    }
    
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        m_infoLabel->setText("File does not exist");
        return;
    }
    
    QString info;
    info += QString("<b>%1</b><br>").arg(fileInfo.fileName());
    info += QString("Size: %1<br>").arg(formatFileSize(fileInfo.size()));
    info += QString("Type: %1<br>").arg(fileInfo.suffix().toUpper());
    info += QString("Modified: %1<br>").arg(fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss"));
    info += QString("Path: %1<br>").arg(fileInfo.absoluteFilePath());
    
    if (fileInfo.isSymLink()) {
        info += QString("Link to: %1<br>").arg(fileInfo.symLinkTarget());
    }
    
    // Add permissions info
    QString permissions;
    if (fileInfo.isReadable()) permissions += "R";
    if (fileInfo.isWritable()) permissions += "W";
    if (fileInfo.isExecutable()) permissions += "X";
    info += QString("Permissions: %1<br>").arg(permissions);
    
    m_infoLabel->setText(info);
}

QString PreviewWidget::formatFileSize(qint64 size) const
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (size >= GB) {
        return QString("%1 GB").arg(size / GB);
    } else if (size >= MB) {
        return QString("%1 MB").arg(size / MB);
    } else if (size >= KB) {
        return QString("%1 KB").arg(size / KB);
    } else {
        return QString("%1 bytes").arg(size);
    }
}

#include "PreviewWidget.moc" 