#include "StatusBarWidget.h"
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QTimer>

StatusBarWidget::StatusBarWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(nullptr)
    , m_fileCountLabel(nullptr)
    , m_selectedCountLabel(nullptr)
    , m_pathLabel(nullptr)
    , m_messageLabel(nullptr)
    , m_progressBar(nullptr)
    , m_messageTimer(nullptr)
    , m_fileCount(0)
    , m_folderCount(0)
    , m_selectedCount(0)
    , m_indexingActive(false)
    , m_searchActive(false)
{
    setupUI();
    
    m_messageTimer = new QTimer(this);
    m_messageTimer->setSingleShot(true);
    connect(m_messageTimer, &QTimer::timeout, this, &StatusBarWidget::onMessageTimeout);
}

StatusBarWidget::~StatusBarWidget()
{
}

void StatusBarWidget::setupUI()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(5, 2, 5, 2);
    m_layout->setSpacing(10);
    
    // File count label
    m_fileCountLabel = new QLabel(this);
    m_fileCountLabel->setStyleSheet("QLabel { color: #ccc; font-size: 11px; }");
    m_fileCountLabel->setMinimumWidth(150);
    
    // Selected count label
    m_selectedCountLabel = new QLabel(this);
    m_selectedCountLabel->setStyleSheet("QLabel { color: #ccc; font-size: 11px; }");
    m_selectedCountLabel->setMinimumWidth(100);
    m_selectedCountLabel->setVisible(false);
    
    // Path label
    m_pathLabel = new QLabel(this);
    m_pathLabel->setStyleSheet("QLabel { color: #999; font-size: 11px; }");
    m_pathLabel->setMinimumWidth(200);
    
    // Message label
    m_messageLabel = new QLabel(this);
    m_messageLabel->setStyleSheet("QLabel { color: #4CAF50; font-size: 11px; }");
    m_messageLabel->setVisible(false);
    
    // Progress bar
    m_progressBar = new QProgressBar(this);
    m_progressBar->setMaximumWidth(200);
    m_progressBar->setMaximumHeight(16);
    m_progressBar->setStyleSheet(
        "QProgressBar {"
        "   border: 1px solid #555;"
        "   border-radius: 3px;"
        "   text-align: center;"
        "   font-size: 10px;"
        "   color: white;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #4CAF50;"
        "   border-radius: 2px;"
        "}"
    );
    m_progressBar->setVisible(false);
    
    // Add widgets to layout
    m_layout->addWidget(m_fileCountLabel);
    m_layout->addWidget(m_selectedCountLabel);
    m_layout->addStretch();
    m_layout->addWidget(m_messageLabel);
    m_layout->addWidget(m_progressBar);
    m_layout->addStretch();
    m_layout->addWidget(m_pathLabel);
    
    updateStatusText();
}

void StatusBarWidget::setFileCount(int files, int folders)
{
    m_fileCount = files;
    m_folderCount = folders;
    updateStatusText();
}

void StatusBarWidget::setSelectedCount(int count)
{
    m_selectedCount = count;
    updateStatusText();
}

void StatusBarWidget::setCurrentPath(const QString &path)
{
    m_currentPath = path;
    
    // Truncate path if too long
    QString displayPath = path;
    const int maxLength = 60;
    if (displayPath.length() > maxLength) {
        displayPath = "..." + displayPath.right(maxLength - 3);
    }
    
    m_pathLabel->setText(displayPath);
    m_pathLabel->setToolTip(path);
}

void StatusBarWidget::setIndexingProgress(int progress)
{
    m_indexingActive = true;
    m_progressBar->setVisible(true);
    m_progressBar->setValue(progress);
    m_progressBar->setFormat(QString("Indexing... %1%").arg(progress));
    
    if (progress >= 100) {
        // Hide progress bar after a short delay
        QTimer::singleShot(1000, this, &StatusBarWidget::setIndexingCompleted);
    }
}

void StatusBarWidget::setIndexingCompleted()
{
    m_indexingActive = false;
    m_progressBar->setVisible(false);
    showMessage("Indexing completed", 2000);
}

void StatusBarWidget::setSearchProgress(int progress)
{
    m_searchActive = true;
    m_progressBar->setVisible(true);
    m_progressBar->setValue(progress);
    m_progressBar->setFormat(QString("Searching... %1%").arg(progress));
    
    if (progress >= 100) {
        // Hide progress bar after a short delay
        QTimer::singleShot(500, this, &StatusBarWidget::setSearchCompleted);
    }
}

void StatusBarWidget::setSearchCompleted()
{
    m_searchActive = false;
    m_progressBar->setVisible(false);
}

void StatusBarWidget::showMessage(const QString &message, int timeout)
{
    m_messageLabel->setText(message);
    m_messageLabel->setVisible(true);
    
    if (timeout > 0) {
        m_messageTimer->start(timeout);
    }
}

void StatusBarWidget::onMessageTimeout()
{
    m_messageLabel->setVisible(false);
    m_messageLabel->clear();
}

void StatusBarWidget::updateStatusText()
{
    QString text;
    
    if (m_selectedCount > 0) {
        text = QString("%1 selected").arg(m_selectedCount);
        m_selectedCountLabel->setText(text);
        m_selectedCountLabel->setVisible(true);
    } else {
        m_selectedCountLabel->setVisible(false);
    }
    
    // File count text
    if (m_fileCount == 0 && m_folderCount == 0) {
        text = "No items";
    } else if (m_folderCount == 0) {
        text = QString("%1 file%2").arg(m_fileCount).arg(m_fileCount == 1 ? "" : "s");
    } else if (m_fileCount == 0) {
        text = QString("%1 folder%2").arg(m_folderCount).arg(m_folderCount == 1 ? "" : "s");
    } else {
        text = QString("%1 file%2, %3 folder%4")
               .arg(m_fileCount).arg(m_fileCount == 1 ? "" : "s")
               .arg(m_folderCount).arg(m_folderCount == 1 ? "" : "s");
    }
    
    m_fileCountLabel->setText(text);
}

#include "StatusBarWidget.moc" 