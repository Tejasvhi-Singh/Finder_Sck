#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTreeView>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QMenuBar>
#include <QStatusBar>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QStyleFactory>
#include <QPalette>

class SimpleFileExplorer : public QMainWindow
{
    Q_OBJECT

public:
    SimpleFileExplorer(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Mac File Explorer - Simple Version");
        setMinimumSize(800, 600);
        
        setupUI();
        setupConnections();
        
        // Set initial directory to home
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        navigateToPath(homePath);
    }

private slots:
    void onSearchTextChanged(const QString &text)
    {
        if (text.isEmpty()) {
            m_fileModel->setNameFilters(QStringList());
        } else {
            m_fileModel->setNameFilters(QStringList() << QString("*%1*").arg(text));
        }
        m_fileModel->setNameFilterDisables(false);
    }
    
    void onTreeSelectionChanged(const QModelIndex &current, const QModelIndex &)
    {
        if (current.isValid()) {
            QString path = m_fileModel->filePath(current);
            if (QFileInfo(path).isDir()) {
                m_listView->setRootIndex(current);
                m_pathEdit->setText(path);
                updateStatusBar(path);
            }
        }
    }
    
    void onListDoubleClicked(const QModelIndex &index)
    {
        if (index.isValid()) {
            QString path = m_fileModel->filePath(index);
            QFileInfo info(path);
            
            if (info.isDir()) {
                navigateToPath(path);
            } else {
                // Open file with default application
                QDesktopServices::openUrl(QUrl::fromLocalFile(path));
            }
        }
    }
    
    void onGoHomeClicked()
    {
        QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        navigateToPath(homePath);
    }
    
    void onGoUpClicked()
    {
        QString currentPath = m_pathEdit->text();
        QDir dir(currentPath);
        if (dir.cdUp()) {
            navigateToPath(dir.absolutePath());
        }
    }
    
    void onRefreshClicked()
    {
        QString currentPath = m_pathEdit->text();
        navigateToPath(currentPath);
    }

private:
    void setupUI()
    {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // Toolbar
        QHBoxLayout *toolbarLayout = new QHBoxLayout();
        
        m_pathEdit = new QLineEdit();
        m_pathEdit->setReadOnly(true);
        
        QPushButton *homeButton = new QPushButton("Home");
        QPushButton *upButton = new QPushButton("Up");
        QPushButton *refreshButton = new QPushButton("Refresh");
        
        m_searchEdit = new QLineEdit();
        m_searchEdit->setPlaceholderText("Search files...");
        m_searchEdit->setMaximumWidth(200);
        
        toolbarLayout->addWidget(new QLabel("Path:"));
        toolbarLayout->addWidget(m_pathEdit);
        toolbarLayout->addWidget(homeButton);
        toolbarLayout->addWidget(upButton);
        toolbarLayout->addWidget(refreshButton);
        toolbarLayout->addWidget(new QLabel("Search:"));
        toolbarLayout->addWidget(m_searchEdit);
        
        mainLayout->addLayout(toolbarLayout);
        
        // Main content area
        QSplitter *splitter = new QSplitter(Qt::Horizontal);
        
        // Left side - tree view
        m_treeView = new QTreeView();
        m_treeView->setMaximumWidth(300);
        m_treeView->setHeaderHidden(true);
        
        // Right side - list view
        m_listView = new QListView();
        m_listView->setViewMode(QListView::ListMode);
        m_listView->setResizeMode(QListView::Adjust);
        
        splitter->addWidget(m_treeView);
        splitter->addWidget(m_listView);
        splitter->setSizes(QList<int>() << 200 << 600);
        
        mainLayout->addWidget(splitter);
        
        // File system model
        m_fileModel = new QFileSystemModel(this);
        m_fileModel->setRootPath("");
        m_fileModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        
        m_treeView->setModel(m_fileModel);
        m_listView->setModel(m_fileModel);
        
        // Hide columns except name in tree view
        for (int i = 1; i < m_fileModel->columnCount(); ++i) {
            m_treeView->hideColumn(i);
        }
        
        // Status bar
        statusBar()->showMessage("Ready");
        
        // Connect button signals
        connect(homeButton, &QPushButton::clicked, this, &SimpleFileExplorer::onGoHomeClicked);
        connect(upButton, &QPushButton::clicked, this, &SimpleFileExplorer::onGoUpClicked);
        connect(refreshButton, &QPushButton::clicked, this, &SimpleFileExplorer::onRefreshClicked);
    }
    
    void setupConnections()
    {
        connect(m_searchEdit, &QLineEdit::textChanged, this, &SimpleFileExplorer::onSearchTextChanged);
        connect(m_treeView->selectionModel(), &QItemSelectionModel::currentChanged, 
                this, &SimpleFileExplorer::onTreeSelectionChanged);
        connect(m_listView, &QListView::doubleClicked, this, &SimpleFileExplorer::onListDoubleClicked);
    }
    
    void navigateToPath(const QString &path)
    {
        QModelIndex index = m_fileModel->index(path);
        if (index.isValid()) {
            m_treeView->setCurrentIndex(index);
            m_treeView->scrollTo(index);
            m_listView->setRootIndex(index);
            m_pathEdit->setText(path);
            updateStatusBar(path);
        }
    }
    
    void updateStatusBar(const QString &path)
    {
        QDir dir(path);
        QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        
        int files = 0, folders = 0;
        for (const QFileInfo &info : entries) {
            if (info.isDir()) {
                folders++;
            } else {
                files++;
            }
        }
        
        QString statusText = QString("%1 file%2, %3 folder%4")
                           .arg(files).arg(files == 1 ? "" : "s")
                           .arg(folders).arg(folders == 1 ? "" : "s");
        statusBar()->showMessage(statusText);
    }

private:
    QFileSystemModel *m_fileModel;
    QTreeView *m_treeView;
    QListView *m_listView;
    QLineEdit *m_pathEdit;
    QLineEdit *m_searchEdit;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Mac File Explorer");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Advanced File Explorer");
    
    // Apply dark theme
    app.setStyle(QStyleFactory::create("Fusion"));
    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    
    app.setPalette(darkPalette);
    
    SimpleFileExplorer window;
    window.show();
    
    return app.exec();
}

#include "main_simple.moc" 