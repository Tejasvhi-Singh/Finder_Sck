#pragma once

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QTimer>

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = nullptr);
    ~StatusBarWidget();

    void setFileCount(int files, int folders);
    void setSelectedCount(int count);
    void setCurrentPath(const QString &path);
    void setIndexingProgress(int progress);
    void setIndexingCompleted();
    void setSearchProgress(int progress);
    void setSearchCompleted();
    void showMessage(const QString &message, int timeout = 3000);

private slots:
    void onMessageTimeout();

private:
    void setupUI();
    void updateStatusText();

    QHBoxLayout *m_layout;
    QLabel *m_fileCountLabel;
    QLabel *m_selectedCountLabel;
    QLabel *m_pathLabel;
    QLabel *m_messageLabel;
    QProgressBar *m_progressBar;
    
    QTimer *m_messageTimer;
    
    int m_fileCount;
    int m_folderCount;
    int m_selectedCount;
    QString m_currentPath;
    bool m_indexingActive;
    bool m_searchActive;
}; 