#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <QRegularExpression>
#include <QDateTime>
#include <QStringList>
#include <QHash>
#include <QVariant>

class AdvancedSearch : public QDialog
{
    Q_OBJECT

public:
    struct SearchParameters {
        QString fileName;
        QString content;
        QString location;
        QStringList fileTypes;
        QStringList excludePatterns;
        
        // Size filters
        bool useSizeFilter;
        qint64 minSize;
        qint64 maxSize;
        
        // Date filters
        bool useDateFilter;
        QDateTime dateFrom;
        QDateTime dateTo;
        
        // Content filters
        bool useContentFilter;
        QString contentText;
        bool contentCaseSensitive;
        bool contentWholeWords;
        bool contentRegex;
        
        // Search options
        bool caseSensitive;
        bool useRegex;
        bool searchSubfolders;
        bool searchHiddenFiles;
        bool searchSystemFiles;
        bool followSymlinks;
        
        // Results options
        int maxResults;
        int timeout;
        
        SearchParameters() :
            useSizeFilter(false),
            minSize(0),
            maxSize(0),
            useDateFilter(false),
            useContentFilter(false),
            contentCaseSensitive(false),
            contentWholeWords(false),
            contentRegex(false),
            caseSensitive(false),
            useRegex(false),
            searchSubfolders(true),
            searchHiddenFiles(false),
            searchSystemFiles(false),
            followSymlinks(false),
            maxResults(10000),
            timeout(30)
        {}
    };

    explicit AdvancedSearch(QWidget *parent = nullptr);
    ~AdvancedSearch();

    SearchParameters getSearchParameters() const;
    void setSearchParameters(const SearchParameters &params);
    
    void saveSearchTemplate(const QString &name);
    void loadSearchTemplate(const QString &name);
    QStringList getSearchTemplates() const;
    void deleteSearchTemplate(const QString &name);

signals:
    void searchRequested(const SearchParameters &params);
    void searchCancelled();

private slots:
    void onSearchClicked();
    void onCancelClicked();
    void onResetClicked();
    void onBrowseLocationClicked();
    void onFileTypeChanged();
    void onSizeFilterToggled(bool enabled);
    void onDateFilterToggled(bool enabled);
    void onContentFilterToggled(bool enabled);
    void onSaveTemplateClicked();
    void onLoadTemplateClicked();
    void onDeleteTemplateClicked();
    void onPreviewRegexClicked();

private:
    void setupUI();
    void setupConnections();
    void updateUI();
    void resetForm();
    void validateForm();
    bool isFormValid() const;
    void showRegexPreview();
    void loadTemplates();
    void saveTemplates();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QGridLayout *m_formLayout;
    
    // Basic search
    QGroupBox *m_basicGroup;
    QLineEdit *m_fileNameEdit;
    QLineEdit *m_locationEdit;
    QPushButton *m_browseLocationButton;
    QComboBox *m_fileTypeCombo;
    QLineEdit *m_excludePatternsEdit;
    
    // Size filters
    QGroupBox *m_sizeGroup;
    QCheckBox *m_useSizeFilterCheck;
    QDoubleSpinBox *m_minSizeSpinBox;
    QDoubleSpinBox *m_maxSizeSpinBox;
    QComboBox *m_sizeUnitCombo;
    
    // Date filters
    QGroupBox *m_dateGroup;
    QCheckBox *m_useDateFilterCheck;
    QDateEdit *m_dateFromEdit;
    QDateEdit *m_dateToEdit;
    QComboBox *m_dateTypeCombo;
    
    // Content filters
    QGroupBox *m_contentGroup;
    QCheckBox *m_useContentFilterCheck;
    QTextEdit *m_contentTextEdit;
    QCheckBox *m_contentCaseSensitiveCheck;
    QCheckBox *m_contentWholeWordsCheck;
    QCheckBox *m_contentRegexCheck;
    
    // Search options
    QGroupBox *m_optionsGroup;
    QCheckBox *m_caseSensitiveCheck;
    QCheckBox *m_useRegexCheck;
    QCheckBox *m_searchSubfoldersCheck;
    QCheckBox *m_searchHiddenFilesCheck;
    QCheckBox *m_searchSystemFilesCheck;
    QCheckBox *m_followSymlinksCheck;
    
    // Results options
    QGroupBox *m_resultsGroup;
    QSpinBox *m_maxResultsSpinBox;
    QSpinBox *m_timeoutSpinBox;
    
    // Templates
    QGroupBox *m_templatesGroup;
    QComboBox *m_templateCombo;
    QPushButton *m_saveTemplateButton;
    QPushButton *m_loadTemplateButton;
    QPushButton *m_deleteTemplateButton;
    
    // Buttons
    QHBoxLayout *m_buttonLayout;
    QPushButton *m_searchButton;
    QPushButton *m_cancelButton;
    QPushButton *m_resetButton;
    QPushButton *m_previewRegexButton;
    
    // Templates storage
    QHash<QString, SearchParameters> m_searchTemplates;
    static const QString TEMPLATES_KEY;
}; 