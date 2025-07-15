#include "config_editor.h"
#include <ui_config_editor.h>

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "settings_manager.h"

ConfigEditor::ConfigEditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigEditor)
    , m_configIO{nullptr}
{
    ui->setupUi(this);
    resize(600, 450);
    setMaximumSize(720, 720);

}

ConfigEditor::~ConfigEditor()
{
    delete ui;
}

void ConfigEditor::addFile()
{
    m_editMode = EditMode::AddNewConfig;
    ui->titleEdit->setText(QString());
    ui->contentEdit->setPlainText(QString());
    exec();
}

void ConfigEditor::openFile()
{
    m_editMode = EditMode::ImportConfig;
    SettingsManager settingsManager;
    QString lastOpenedFilePath = settingsManager.lastOpenedFilePath();
    if (lastOpenedFilePath.isEmpty()) {
        lastOpenedFilePath = QDir::homePath();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Select JSON file"),
                                                    lastOpenedFilePath,
                                                    tr("JSON File (*.json)")
                                                    );
    qDebug() << filePath;
    m_configIO = std::make_unique<ConfigIO>(filePath);
    if (!filePath.isEmpty()) {
        QString fileContent = m_configIO->openConfigFile();
        if (fileContent.isEmpty()) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Import config failed.")
                                  );
            return;
        }
        QString fileBaseName = QFileInfo(filePath).baseName();
        ui->titleEdit->setText(fileBaseName);
        ui->contentEdit->setPlainText(fileContent);
        settingsManager.setLastOpenedFilePath(QFileInfo(filePath).absolutePath());
        exec();
    }
}

void ConfigEditor::openFile(int index, const QString &filePath, const QString &title)
{
    m_editMode = EditMode::EditConfig;
    m_configFileIndex = index;
    m_configIO = std::make_unique<ConfigIO>(filePath);
    if (!filePath.isEmpty()) {
        if (!m_configIO->fileConfigExists()) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("The configuration file does not exist or has been deleted.")
                                 );
            return;
        }
        QString fileContent = m_configIO->openConfigFile();
        if (fileContent.isEmpty()) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Open config failed.")
                                  );
            return;
        }
        ui->titleEdit->setText(title);
        ui->contentEdit->setPlainText(fileContent);
        exec();
    }
}

void ConfigEditor::saveConfigFile(const QString &configContent)
{
    switch (m_editMode) {
    case EditMode::AddNewConfig:
    case EditMode::ImportConfig:
        m_configIO = std::make_unique<ConfigIO>();
        break;
    default:
        break;
    }
    m_configIO->saveConfigFile(configContent);

    switch (m_editMode) {
    case EditMode::AddNewConfig:
    case EditMode::ImportConfig:
        emit configFileSaved(QFileInfo(m_configIO->getConfigFilePath()).absoluteFilePath(),
                             ui->titleEdit->text());
        break;
    case EditMode::EditConfig:
        emit editedConfigFileSaved(m_configFileIndex,
                                   m_configIO->getConfigFilePath(),
                                   ui->titleEdit->text());
    default:
        break;
    }
}

void ConfigEditor::on_saveButton_clicked()
{
    if (ui->titleEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("The title can not be blank.")
                             );
        return;
    }
    saveConfigFile(ui->contentEdit->toPlainText());
    close();
}

void ConfigEditor::on_cancelButton_clicked()
{
    close();
}

