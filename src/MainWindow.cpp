#include "MainWindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QStandardPaths>
#include <QShortcut>
#include <QKeySequence>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainSplitter(nullptr)
    , m_leftSplitter(nullptr)
    , m_directoryTree(nullptr)
    , m_fileList(nullptr)
    , m_detailView(nullptr)
    , m_searchField(nullptr)
    , m_searchScope(nullptr)
    , m_advancedSearchButton(nullptr)
    , m_searchProgress(nullptr)
    , m_backButton(nullptr)
    , m_forwardButton(nullptr)
    , m_upButton(nullptr)
    , m_homeButton(nullptr)
    , m_refreshButton(nullptr)
    , m_pathBar(nullptr)
    , m_viewMode(nullptr)
    , m_sortingMode(nullptr)
    , m_showHiddenButton(nullptr)
    , m_previewWidget(nullptr)
    , m_statusWidget(nullptr)
    , m_fileWatcher(nullptr)
    , m_searchTimer(nullptr)
    , m_currentHistoryIndex(-1)
    , m_isSearchMode(false)
    , m_showHiddenFiles(false)
    , m_indexingThread(nullptr)
    , m_contextMenu(nullptr)
{
    setWindowTitle("Mac File Explorer");
    setMinimumSize(1200, 800);
    resize(1600, 1000);
    
    // Initialize core components
    m_fileSystemModel = std::make_unique<FileSystemModel>(this);
    m_searchEngine = std::make_unique<SearchEngine>(this);
    m_fileIndexer = std::make_unique<FileIndexer>(this);
    m_advancedSearch = std::make_unique<AdvancedSearch>(this);
    m_macOSIntegration = std::make_unique<MacOSIntegration>(this);
    
    // Setup UI
    setupUI();
    setupMenus();
    setupToolBars();
    setupStatusBar();
    setupConnections();
    setupFileWatcher();
    
    // Initialize with home directory
    m_currentPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    navigateToPath(m_currentPath);
    
    // Start background indexing
    m_fileIndexer->startIndexing();
    
    // Load settings
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    
    if (m_indexingThread && m_indexingThread->isRunning()) {
        m_indexingThread->quit();
        m_indexingThread->wait();
    }
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);
    
    // Search bar
    QHBoxLayout *searchLayout = new QHBoxLayout();
    
    m_searchField = new QLineEdit(this);
    m_searchField->setPlaceholderText("Search files and folders...");
    m_searchField->setStyleSheet("QLineEdit { padding: 8px; font-size: 14px; border: 2px solid #555; border-radius: 20px; }");
    
    m_searchScope = new QComboBox(this);
    m_searchScope->addItems({"Current Folder", "This Mac", "Documents", "Downloads", "Pictures", "Music", "Videos"});
    m_searchScope->setStyleSheet("QComboBox { padding: 8px; font-size: 12px; }");
    
    m_advancedSearchButton = new QPushButton("Advanced", this);
    m_advancedSearchButton->setStyleSheet("QPushButton { padding: 8px 16px; font-size: 12px; }");
    
    m_searchProgress = new QProgressBar(this);
    m_searchProgress->setVisible(false);
    m_searchProgress->setStyleSheet("QProgressBar { border: 2px solid #555; border-radius: 5px; text-align: center; }");
    
    searchLayout->addWidget(m_searchField);
    searchLayout->addWidget(m_searchScope);
    searchLayout->addWidget(m_advancedSearchButton);
    searchLayout->addWidget(m_searchProgress);
    
    mainLayout->addLayout(searchLayout);
    
    // Main splitter
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    // Left panel splitter
    m_leftSplitter = new QSplitter(Qt::Vertical, this);
    
    // Directory tree
    m_directoryTree = new QTreeView(this);
    m_directoryTree->setModel(m_fileSystemModel.get());
    m_directoryTree->setRootIndex(m_fileSystemModel->index(m_currentPath));
    m_directoryTree->setHeaderHidden(true);
    m_directoryTree->setStyleSheet("QTreeView { border: 1px solid #555; background-color: #2a2a2a; }");
    
    // File list/detail view
    m_fileList = new QListView(this);
    m_fileList->setModel(m_fileSystemModel.get());
    m_fileList->setRootIndex(m_fileSystemModel->index(m_currentPath));
    m_fileList->setStyleSheet("QListView { border: 1px solid #555; background-color: #2a2a2a; }");
    
    m_detailView = new QTreeView(this);
    m_detailView->setModel(m_fileSystemModel.get());
    m_detailView->setRootIndex(m_fileSystemModel->index(m_currentPath));
    m_detailView->setAlternatingRowColors(true);
    m_detailView->setStyleSheet("QTreeView { border: 1px solid #555; background-color: #2a2a2a; }");
    m_detailView->setVisible(false);
    
    // Preview widget
    m_previewWidget = new PreviewWidget(this);
    m_previewWidget->setStyleSheet("QWidget { border: 1px solid #555; background-color: #2a2a2a; }");
    
    // Setup left panel
    m_leftSplitter->addWidget(m_directoryTree);
    m_leftSplitter->addWidget(m_fileList);
    m_leftSplitter->addWidget(m_detailView);
    m_leftSplitter->setSizes({300, 400});
    
    // Setup main splitter
    m_mainSplitter->addWidget(m_leftSplitter);
    m_mainSplitter->addWidget(m_previewWidget);
    m_mainSplitter->setSizes({800, 300});
    
    mainLayout->addWidget(m_mainSplitter);
    
    // Setup search timer
    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    m_searchTimer->setInterval(300); // 300ms delay for search
}

void MainWindow::setupMenus()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *newFolderAction = new QAction("New &Folder", this);
    newFolderAction->setShortcut(QKeySequence::New);
    fileMenu->addAction(newFolderAction);
    
    fileMenu->addSeparator();
    
    QAction *copyAction = new QAction("&Copy", this);
    copyAction->setShortcut(QKeySequence::Copy);
    fileMenu->addAction(copyAction);
    
    QAction *pasteAction = new QAction("&Paste", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    fileMenu->addAction(pasteAction);
    
    QAction *deleteAction = new QAction("&Delete", this);
    deleteAction->setShortcut(QKeySequence::Delete);
    fileMenu->addAction(deleteAction);
    
    fileMenu->addSeparator();
    
    QAction *propertiesAction = new QAction("&Properties", this);
    propertiesAction->setShortcut(QKeySequence("Cmd+I"));
    fileMenu->addAction(propertiesAction);
    
    // Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    
    QAction *selectAllAction = new QAction("Select &All", this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    editMenu->addAction(selectAllAction);
    
    QAction *findAction = new QAction("&Find", this);
    findAction->setShortcut(QKeySequence::Find);
    editMenu->addAction(findAction);
    
    // View menu
    QMenu *viewMenu = menuBar()->addMenu("&View");
    
    QAction *refreshAction = new QAction("&Refresh", this);
    refreshAction->setShortcut(QKeySequence::Refresh);
    viewMenu->addAction(refreshAction);
    
    viewMenu->addSeparator();
    
    QAction *showHiddenAction = new QAction("Show &Hidden Files", this);
    showHiddenAction->setCheckable(true);
    showHiddenAction->setShortcut(QKeySequence("Cmd+Shift+."));
    viewMenu->addAction(showHiddenAction);
    
    // Go menu
    QMenu *goMenu = menuBar()->addMenu("&Go");
    
    QAction *backAction = new QAction("&Back", this);
    backAction->setShortcut(QKeySequence::Back);
    goMenu->addAction(backAction);
    
    QAction *forwardAction = new QAction("&Forward", this);
    forwardAction->setShortcut(QKeySequence::Forward);
    goMenu->addAction(forwardAction);
    
    QAction *upAction = new QAction("&Up", this);
    upAction->setShortcut(QKeySequence("Cmd+Up"));
    goMenu->addAction(upAction);
    
    QAction *homeAction = new QAction("&Home", this);
    homeAction->setShortcut(QKeySequence("Cmd+Home"));
    goMenu->addAction(homeAction);
    
    // Connect actions
    connect(newFolderAction, &QAction::triggered, this, &MainWindow::onNewFolder);
    connect(copyAction, &QAction::triggered, this, &MainWindow::onCopySelected);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::onPasteClipboard);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteSelected);
    connect(propertiesAction, &QAction::triggered, this, &MainWindow::onShowProperties);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::onRefreshView);
    connect(showHiddenAction, &QAction::toggled, this, &MainWindow::onShowHiddenFiles);
    connect(backAction, &QAction::triggered, this, &MainWindow::onNavigateBack);
    connect(forwardAction, &QAction::triggered, this, &MainWindow::onNavigateForward);
    connect(upAction, &QAction::triggered, this, &MainWindow::onNavigateUp);
    connect(homeAction, &QAction::triggered, this, &MainWindow::onNavigateHome);
}

void MainWindow::setupToolBars()
{
    QToolBar *mainToolBar = addToolBar("Main");
    mainToolBar->setMovable(false);
    mainToolBar->setStyleSheet("QToolBar { border: none; spacing: 5px; }");
    
    // Navigation buttons
    m_backButton = new QPushButton("◀", this);
    m_backButton->setEnabled(false);
    m_backButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    m_forwardButton = new QPushButton("▶", this);
    m_forwardButton->setEnabled(false);
    m_forwardButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    m_upButton = new QPushButton("↑", this);
    m_upButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    m_homeButton = new QPushButton("🏠", this);
    m_homeButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    m_refreshButton = new QPushButton("🔄", this);
    m_refreshButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    // Path bar
    m_pathBar = new QLineEdit(this);
    m_pathBar->setReadOnly(true);
    m_pathBar->setStyleSheet("QLineEdit { padding: 8px; font-size: 12px; border: 1px solid #555; }");
    
    // View controls
    m_viewMode = new QComboBox(this);
    m_viewMode->addItems({"List View", "Detail View", "Icon View"});
    m_viewMode->setStyleSheet("QComboBox { padding: 8px; font-size: 12px; }");
    
    m_sortingMode = new QComboBox(this);
    m_sortingMode->addItems({"Name", "Size", "Type", "Date Modified", "Date Created"});
    m_sortingMode->setStyleSheet("QComboBox { padding: 8px; font-size: 12px; }");
    
    m_showHiddenButton = new QPushButton("👁", this);
    m_showHiddenButton->setCheckable(true);
    m_showHiddenButton->setStyleSheet("QPushButton { padding: 8px 12px; font-size: 16px; }");
    
    // Add to toolbar
    mainToolBar->addWidget(m_backButton);
    mainToolBar->addWidget(m_forwardButton);
    mainToolBar->addWidget(m_upButton);
    mainToolBar->addWidget(m_homeButton);
    mainToolBar->addWidget(m_refreshButton);
    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_pathBar);
    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_viewMode);
    mainToolBar->addWidget(m_sortingMode);
    mainToolBar->addWidget(m_showHiddenButton);
}

void MainWindow::setupStatusBar()
{
    m_statusWidget = new StatusBarWidget(this);
    statusBar()->addPermanentWidget(m_statusWidget);
}

void MainWindow::setupConnections()
{
    // Navigation
    connect(m_backButton, &QPushButton::clicked, this, &MainWindow::onNavigateBack);
    connect(m_forwardButton, &QPushButton::clicked, this, &MainWindow::onNavigateForward);
    connect(m_upButton, &QPushButton::clicked, this, &MainWindow::onNavigateUp);
    connect(m_homeButton, &QPushButton::clicked, this, &MainWindow::onNavigateHome);
    connect(m_refreshButton, &QPushButton::clicked, this, &MainWindow::onRefreshView);
    
    // Search
    connect(m_searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(m_advancedSearchButton, &QPushButton::clicked, this, &MainWindow::onAdvancedSearchRequested);
    connect(m_searchTimer, &QTimer::timeout, [this]() {
        if (!m_searchField->text().isEmpty()) {
            m_searchEngine->search(m_searchField->text(), m_currentPath);
        }
    });
    
    // View controls
    connect(m_viewMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onViewModeChanged);
    connect(m_sortingMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSortingChanged);
    connect(m_showHiddenButton, &QPushButton::toggled, this, &MainWindow::onShowHiddenFiles);
    
    // File selection
    connect(m_directoryTree->selectionModel(), &QItemSelectionModel::currentChanged, 
            this, &MainWindow::onFileSelectionChanged);
    connect(m_fileList->selectionModel(), &QItemSelectionModel::currentChanged, 
            this, &MainWindow::onFileSelectionChanged);
    connect(m_detailView->selectionModel(), &QItemSelectionModel::currentChanged, 
            this, &MainWindow::onFileSelectionChanged);
    
    // Search engine
    connect(m_searchEngine.get(), &SearchEngine::searchCompleted, this, &MainWindow::onSearchCompleted);
    connect(m_searchEngine.get(), &SearchEngine::searchProgress, m_searchProgress, &QProgressBar::setValue);
    
    // File indexer
    connect(m_fileIndexer.get(), &FileIndexer::indexingProgress, this, &MainWindow::onIndexingProgress);
    connect(m_fileIndexer.get(), &FileIndexer::indexingCompleted, this, &MainWindow::onIndexingCompleted);
}

void MainWindow::setupFileWatcher()
{
    m_fileWatcher = new QFileSystemWatcher(this);
    connect(m_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::onDirectoryChanged);
}

void MainWindow::onDirectoryChanged(const QString &path)
{
    if (path == m_currentPath) {
        onRefreshView();
    }
}

void MainWindow::onFileSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    
    if (current.isValid()) {
        QString filePath = m_fileSystemModel->filePath(current);
        onPreviewFile(filePath);
        updateStatusBar();
    }
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    m_searchTimer->stop();
    
    if (text.isEmpty()) {
        m_isSearchMode = false;
        m_fileList->setRootIndex(m_fileSystemModel->index(m_currentPath));
        m_detailView->setRootIndex(m_fileSystemModel->index(m_currentPath));
        m_searchProgress->setVisible(false);
    } else {
        m_isSearchMode = true;
        m_searchProgress->setVisible(true);
        m_searchTimer->start();
    }
}

void MainWindow::onSearchCompleted(const QList<SearchEngine::SearchResult> &results)
{
    m_searchProgress->setVisible(false);
    // Update view with search results
    // This would require a custom model for search results
    qDebug() << "Search completed with" << results.size() << "results";
}

void MainWindow::onIndexingProgress(int progress)
{
    m_statusWidget->setIndexingProgress(progress);
}

void MainWindow::onIndexingCompleted()
{
    m_statusWidget->setIndexingCompleted();
}

void MainWindow::onAdvancedSearchRequested()
{
    m_advancedSearch->show();
}

void MainWindow::onNavigateBack()
{
    if (m_currentHistoryIndex > 0) {
        m_currentHistoryIndex--;
        QString path = m_navigationHistory[m_currentHistoryIndex];
        navigateToPath(path);
        updateNavigationButtons();
    }
}

void MainWindow::onNavigateForward()
{
    if (m_currentHistoryIndex < m_navigationHistory.size() - 1) {
        m_currentHistoryIndex++;
        QString path = m_navigationHistory[m_currentHistoryIndex];
        navigateToPath(path);
        updateNavigationButtons();
    }
}

void MainWindow::onNavigateUp()
{
    QDir currentDir(m_currentPath);
    if (currentDir.cdUp()) {
        navigateToPath(currentDir.absolutePath());
    }
}

void MainWindow::onNavigateHome()
{
    navigateToPath(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
}

void MainWindow::onRefreshView()
{
    m_fileSystemModel->refresh();
}

void MainWindow::onViewModeChanged()
{
    int mode = m_viewMode->currentIndex();
    switch (mode) {
        case 0: // List View
            m_fileList->setVisible(true);
            m_detailView->setVisible(false);
            break;
        case 1: // Detail View
            m_fileList->setVisible(false);
            m_detailView->setVisible(true);
            break;
        case 2: // Icon View
            m_fileList->setVisible(true);
            m_detailView->setVisible(false);
            m_fileList->setViewMode(QListView::IconMode);
            break;
    }
}

void MainWindow::onSortingChanged()
{
    int sortColumn = m_sortingMode->currentIndex();
    m_fileSystemModel->sort(sortColumn, Qt::AscendingOrder);
}

void MainWindow::onShowHiddenFiles(bool show)
{
    m_showHiddenFiles = show;
    m_fileSystemModel->setShowHidden(show);
}

void MainWindow::onNewFolder()
{
    bool ok;
    QString name = QInputDialog::getText(this, "New Folder", "Folder name:", QLineEdit::Normal, "New Folder", &ok);
    if (ok && !name.isEmpty()) {
        QString path = m_currentPath + "/" + name;
        QDir().mkpath(path);
    }
}

void MainWindow::onDeleteSelected()
{
    // Implementation for delete operation
}

void MainWindow::onCopySelected()
{
    // Implementation for copy operation
}

void MainWindow::onPasteClipboard()
{
    // Implementation for paste operation
}

void MainWindow::onRenameSelected()
{
    // Implementation for rename operation
}

void MainWindow::onShowProperties()
{
    // Implementation for properties dialog
}

void MainWindow::onPreviewFile(const QString &filePath)
{
    m_previewWidget->setFile(filePath);
}

void MainWindow::navigateToPath(const QString &path)
{
    m_currentPath = path;
    m_pathBar->setText(path);
    
    // Update views
    QModelIndex index = m_fileSystemModel->index(path);
    m_directoryTree->setRootIndex(index);
    m_fileList->setRootIndex(index);
    m_detailView->setRootIndex(index);
    
    // Update file watcher
    m_fileWatcher->removePaths(m_fileWatcher->directories());
    m_fileWatcher->addPath(path);
    
    // Add to history
    addToHistory(path);
    updateNavigationButtons();
    updateStatusBar();
}

void MainWindow::addToHistory(const QString &path)
{
    if (m_currentHistoryIndex >= 0 && m_currentHistoryIndex < m_navigationHistory.size()) {
        // Remove forward history if navigating to a new path
        m_navigationHistory.erase(m_navigationHistory.begin() + m_currentHistoryIndex + 1, 
                                 m_navigationHistory.end());
    }
    
    m_navigationHistory.append(path);
    m_currentHistoryIndex = m_navigationHistory.size() - 1;
}

void MainWindow::updateNavigationButtons()
{
    m_backButton->setEnabled(m_currentHistoryIndex > 0);
    m_forwardButton->setEnabled(m_currentHistoryIndex < m_navigationHistory.size() - 1);
}

void MainWindow::updateStatusBar()
{
    QDir dir(m_currentPath);
    int fileCount = dir.entryList(QDir::Files).count();
    int folderCount = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
    
    m_statusWidget->setFileCount(fileCount, folderCount);
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("currentPath", m_currentPath);
    settings.setValue("showHiddenFiles", m_showHiddenFiles);
    settings.setValue("viewMode", m_viewMode->currentIndex());
    settings.setValue("sortingMode", m_sortingMode->currentIndex());
    settings.setValue("recentSearches", m_recentSearches);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    
    QString savedPath = settings.value("currentPath").toString();
    if (!savedPath.isEmpty() && QDir(savedPath).exists()) {
        navigateToPath(savedPath);
    }
    
    m_showHiddenFiles = settings.value("showHiddenFiles", false).toBool();
    m_showHiddenButton->setChecked(m_showHiddenFiles);
    m_fileSystemModel->setShowHidden(m_showHiddenFiles);
    
    m_viewMode->setCurrentIndex(settings.value("viewMode", 0).toInt());
    m_sortingMode->setCurrentIndex(settings.value("sortingMode", 0).toInt());
    
    m_recentSearches = settings.value("recentSearches").toStringList();
}

#include "MainWindow.moc" 