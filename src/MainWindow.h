#pragma once

#include <QMainWindow>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QLineEdit>
#include <QLabel>
#include <QProgressBar>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QThread>
#include <QMutex>
#include <QHash>
#include <QSortFilterProxyModel>
#include <memory>

#include "FileSystemModel.h"
#include "SearchEngine.h"
#include "FileIndexer.h"
#include "AdvancedSearch.h"
#include "MacOSIntegration.h"
#include "PreviewWidget.h"
#include "StatusBarWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDirectoryChanged(const QString &path);
    void onFileSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onSearchTextChanged(const QString &text);
    void onSearchCompleted(const QList<SearchEngine::SearchResult> &results);
    void onIndexingProgress(int progress);
    void onIndexingCompleted();
    void onAdvancedSearchRequested();
    void onNavigateBack();
    void onNavigateForward();
    void onNavigateUp();
    void onNavigateHome();
    void onRefreshView();
    void onViewModeChanged();
    void onSortingChanged();
    void onShowHiddenFiles(bool show);
    void onNewFolder();
    void onDeleteSelected();
    void onCopySelected();
    void onPasteClipboard();
    void onRenameSelected();
    void onShowProperties();
    void onPreviewFile(const QString &filePath);

private:
    void setupUI();
    void setupMenus();
    void setupToolBars();
    void setupStatusBar();
    void setupConnections();
    void setupFileWatcher();
    void updateNavigationButtons();
    void updateStatusBar();
    void navigateToPath(const QString &path);
    void addToHistory(const QString &path);
    void createContextMenu();
    void showContextMenu(const QPoint &position);
    void applySettings();
    void saveSettings();
    void loadSettings();

    // UI Components
    QWidget *m_centralWidget;
    QSplitter *m_mainSplitter;
    QSplitter *m_leftSplitter;
    
    // Navigation and views
    QTreeView *m_directoryTree;
    QListView *m_fileList;
    QTreeView *m_detailView;
    
    // Search components
    QLineEdit *m_searchField;
    QComboBox *m_searchScope;
    QPushButton *m_advancedSearchButton;
    QProgressBar *m_searchProgress;
    
    // Navigation
    QPushButton *m_backButton;
    QPushButton *m_forwardButton;
    QPushButton *m_upButton;
    QPushButton *m_homeButton;
    QPushButton *m_refreshButton;
    QLineEdit *m_pathBar;
    
    // View controls
    QComboBox *m_viewMode;
    QComboBox *m_sortingMode;
    QPushButton *m_showHiddenButton;
    
    // Preview and status
    PreviewWidget *m_previewWidget;
    StatusBarWidget *m_statusWidget;
    
    // Core components
    std::unique_ptr<FileSystemModel> m_fileSystemModel;
    std::unique_ptr<SearchEngine> m_searchEngine;
    std::unique_ptr<FileIndexer> m_fileIndexer;
    std::unique_ptr<AdvancedSearch> m_advancedSearch;
    std::unique_ptr<MacOSIntegration> m_macOSIntegration;
    
    // File system monitoring
    QFileSystemWatcher *m_fileWatcher;
    QTimer *m_searchTimer;
    
    // Navigation history
    QStringList m_navigationHistory;
    int m_currentHistoryIndex;
    
    // State
    QString m_currentPath;
    bool m_isSearchMode;
    bool m_showHiddenFiles;
    
    // Threading
    QThread *m_indexingThread;
    QMutex m_searchMutex;
    
    // Context menu
    QMenu *m_contextMenu;
    
    // Recent searches
    QStringList m_recentSearches;
    static const int MAX_RECENT_SEARCHES = 20;
}; 