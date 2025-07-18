#pragma once

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileInfo>
#include <QTimer>
#include <QMutex>
#include <QHash>
#include <memory>

class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget *parent = nullptr);
    ~PreviewWidget();

    void setFile(const QString &filePath);
    void clearPreview();
    bool isPreviewSupported(const QString &filePath) const;

signals:
    void previewLoaded(const QString &filePath);
    void previewError(const QString &error);

private slots:
    void onPreviewLoaded();

private:
    void setupUI();
    void loadPreview(const QString &filePath);
    void loadImagePreview(const QString &filePath);
    void loadTextPreview(const QString &filePath);
    void loadVideoPreview(const QString &filePath);
    void loadAudioPreview(const QString &filePath);
    void loadDocumentPreview(const QString &filePath);
    void showFileInfo(const QString &filePath);
    QString formatFileSize(qint64 size) const;

    QVBoxLayout *m_layout;
    QLabel *m_imageLabel;
    QTextEdit *m_textEdit;
    QScrollArea *m_scrollArea;
    QLabel *m_infoLabel;
    
    QString m_currentFile;
    QTimer *m_loadTimer;
    QMutex m_loadMutex;
    
    // Cache for previews
    QHash<QString, QPixmap> m_imageCache;
    QHash<QString, QString> m_textCache;
}; 