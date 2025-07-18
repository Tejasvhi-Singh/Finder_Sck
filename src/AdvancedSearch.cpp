#include "AdvancedSearch.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QSettings>

const QString AdvancedSearch::TEMPLATES_KEY = "searchTemplates";

AdvancedSearch::AdvancedSearch(QWidget *parent)
    : QDialog(parent)
    , m_mainLayout(nullptr)
    , m_formLayout(nullptr)
    , m_basicGroup(nullptr)
    , m_fileNameEdit(nullptr)
    , m_locationEdit(nullptr)
    , m_browseLocationButton(nullptr)
    , m_fileTypeCombo(nullptr)
    , m_excludePatternsEdit(nullptr)
    , m_sizeGroup(nullptr)
    , m_useSizeFilterCheck(nullptr)
    , m_minSizeSpinBox(nullptr)
    , m_maxSizeSpinBox(nullptr)
    , m_sizeUnitCombo(nullptr)
    , m_dateGroup(nullptr)
    , m_useDateFilterCheck(nullptr)
    , m_dateFromEdit(nullptr)
    , m_dateToEdit(nullptr)
    , m_dateTypeCombo(nullptr)
    , m_contentGroup(nullptr)
    , m_useContentFilterCheck(nullptr)
    , m_contentTextEdit(nullptr)
    , m_contentCaseSensitiveCheck(nullptr)
    , m_contentWholeWordsCheck(nullptr)
    , m_contentRegexCheck(nullptr)
    , m_optionsGroup(nullptr)
    , m_caseSensitiveCheck(nullptr)
    , m_useRegexCheck(nullptr)
    , m_searchSubfoldersCheck(nullptr)
    , m_searchHiddenFilesCheck(nullptr)
    , m_searchSystemFilesCheck(nullptr)
    , m_followSymlinksCheck(nullptr)
    , m_resultsGroup(nullptr)
    , m_maxResultsSpinBox(nullptr)
    , m_timeoutSpinBox(nullptr)
    , m_templatesGroup(nullptr)
    , m_templateCombo(nullptr)
    , m_saveTemplateButton(nullptr)
    , m_loadTemplateButton(nullptr)
    , m_deleteTemplateButton(nullptr)
    , m_buttonLayout(nullptr)
    , m_searchButton(nullptr)
    , m_cancelButton(nullptr)
    , m_resetButton(nullptr)
    , m_previewRegexButton(nullptr)
{
    setWindowTitle("Advanced Search");
    setModal(true);
    resize(500, 600);
    
    setupUI();
    setupConnections();
    loadTemplates();
}

AdvancedSearch::~AdvancedSearch()
{
    saveTemplates();
}

void AdvancedSearch::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Basic search group
    m_basicGroup = new QGroupBox("Basic Search", this);
    m_formLayout = new QGridLayout(m_basicGroup);
    
    m_formLayout->addWidget(new QLabel("File name:"), 0, 0);
    m_fileNameEdit = new QLineEdit(this);
    m_formLayout->addWidget(m_fileNameEdit, 0, 1);
    
    m_formLayout->addWidget(new QLabel("Location:"), 1, 0);
    m_locationEdit = new QLineEdit(this);
    m_browseLocationButton = new QPushButton("Browse...", this);
    QHBoxLayout *locationLayout = new QHBoxLayout();
    locationLayout->addWidget(m_locationEdit);
    locationLayout->addWidget(m_browseLocationButton);
    m_formLayout->addLayout(locationLayout, 1, 1);
    
    m_formLayout->addWidget(new QLabel("File type:"), 2, 0);
    m_fileTypeCombo = new QComboBox(this);
    m_fileTypeCombo->addItems({"All Files", "Images", "Documents", "Videos", "Audio", "Archives"});
    m_formLayout->addWidget(m_fileTypeCombo, 2, 1);
    
    m_formLayout->addWidget(new QLabel("Exclude patterns:"), 3, 0);
    m_excludePatternsEdit = new QLineEdit(this);
    m_formLayout->addWidget(m_excludePatternsEdit, 3, 1);
    
    m_mainLayout->addWidget(m_basicGroup);
    
    // Create buttons
    m_buttonLayout = new QHBoxLayout();
    m_searchButton = new QPushButton("Search", this);
    m_cancelButton = new QPushButton("Cancel", this);
    m_resetButton = new QPushButton("Reset", this);
    
    m_buttonLayout->addStretch();
    m_buttonLayout->addWidget(m_resetButton);
    m_buttonLayout->addWidget(m_cancelButton);
    m_buttonLayout->addWidget(m_searchButton);
    
    m_mainLayout->addLayout(m_buttonLayout);
    
    // Set default button
    m_searchButton->setDefault(true);
    
    // TODO: Add other groups (size, date, content, options, results, templates)
    // For now, just create a basic functional dialog
}

void AdvancedSearch::setupConnections()
{
    connect(m_searchButton, &QPushButton::clicked, this, &AdvancedSearch::onSearchClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &AdvancedSearch::onCancelClicked);
    connect(m_resetButton, &QPushButton::clicked, this, &AdvancedSearch::onResetClicked);
    connect(m_browseLocationButton, &QPushButton::clicked, this, &AdvancedSearch::onBrowseLocationClicked);
}

AdvancedSearch::SearchParameters AdvancedSearch::getSearchParameters() const
{
    SearchParameters params;
    params.fileName = m_fileNameEdit->text();
    params.location = m_locationEdit->text();
    
    QString fileType = m_fileTypeCombo->currentText();
    if (fileType != "All Files") {
        params.fileTypes << fileType.toLower();
    }
    
    QString excludePatterns = m_excludePatternsEdit->text();
    if (!excludePatterns.isEmpty()) {
        params.excludePatterns = excludePatterns.split(',', Qt::SkipEmptyParts);
    }
    
    return params;
}

void AdvancedSearch::setSearchParameters(const SearchParameters &params)
{
    m_fileNameEdit->setText(params.fileName);
    m_locationEdit->setText(params.location);
    
    if (!params.fileTypes.isEmpty()) {
        QString fileType = params.fileTypes.first();
        int index = m_fileTypeCombo->findText(fileType, Qt::MatchFixedString);
        if (index >= 0) {
            m_fileTypeCombo->setCurrentIndex(index);
        }
    }
    
    m_excludePatternsEdit->setText(params.excludePatterns.join(","));
}

void AdvancedSearch::onSearchClicked()
{
    SearchParameters params = getSearchParameters();
    emit searchRequested(params);
    accept();
}

void AdvancedSearch::onCancelClicked()
{
    emit searchCancelled();
    reject();
}

void AdvancedSearch::onResetClicked()
{
    resetForm();
}

void AdvancedSearch::onBrowseLocationClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Search Location", m_locationEdit->text());
    if (!dir.isEmpty()) {
        m_locationEdit->setText(dir);
    }
}

void AdvancedSearch::resetForm()
{
    m_fileNameEdit->clear();
    m_locationEdit->clear();
    m_fileTypeCombo->setCurrentIndex(0);
    m_excludePatternsEdit->clear();
}

void AdvancedSearch::loadTemplates()
{
    QSettings settings;
    // TODO: Load search templates from settings
}

void AdvancedSearch::saveTemplates()
{
    QSettings settings;
    // TODO: Save search templates to settings
}

// Stub implementations for other methods
void AdvancedSearch::updateUI() {}
void AdvancedSearch::validateForm() {}
bool AdvancedSearch::isFormValid() const { return true; }
void AdvancedSearch::showRegexPreview() {}
void AdvancedSearch::saveSearchTemplate(const QString &name) { Q_UNUSED(name) }
void AdvancedSearch::loadSearchTemplate(const QString &name) { Q_UNUSED(name) }
QStringList AdvancedSearch::getSearchTemplates() const { return QStringList(); }
void AdvancedSearch::deleteSearchTemplate(const QString &name) { Q_UNUSED(name) }
void AdvancedSearch::onFileTypeChanged() {}
void AdvancedSearch::onSizeFilterToggled(bool enabled) { Q_UNUSED(enabled) }
void AdvancedSearch::onDateFilterToggled(bool enabled) { Q_UNUSED(enabled) }
void AdvancedSearch::onContentFilterToggled(bool enabled) { Q_UNUSED(enabled) }
void AdvancedSearch::onSaveTemplateClicked() {}
void AdvancedSearch::onLoadTemplateClicked() {}
void AdvancedSearch::onDeleteTemplateClicked() {}
void AdvancedSearch::onPreviewRegexClicked() {}

#include "AdvancedSearch.moc" 