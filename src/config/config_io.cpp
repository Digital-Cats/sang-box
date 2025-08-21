#include "config_io.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>

namespace config {

ConfigIO::ConfigIO()
    : m_configFilePath(getConfigsFolder() + "/" + generateFileName())
{}

ConfigIO::ConfigIO(const QString& filePath)
    : m_configFilePath(filePath)
{}

const QString& ConfigIO::getConfigFilePath() const noexcept
{
    return m_configFilePath;
}

void ConfigIO::saveConfigFile(const QString &configContent)
{
    QString directory = getConfigsFolder();
    QDir dir;
    // If the directory does not exist, create the directory
    if (!dir.exists(directory)) {
        dir.mkpath(directory);
    }

    QFile file(m_configFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream textStream(&file);
        textStream << configContent;
        file.close();
    }
}

QString ConfigIO::openConfigFile()
{
    if (!fileConfigExists())
        return {}; // add exception
    QFile file(m_configFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {}; // add exception
    }
    QTextStream textStream(&file);
    QString fileContent = textStream.readAll();
    file.close();
    return fileContent;
}

bool ConfigIO::fileConfigExists() const
{
    return QFile::exists(m_configFilePath);
}

QString ConfigIO::getConfigsFolder()
{
    return QString("./config");
}

QString ConfigIO::generateFileName() const
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timestamp = QString::number(currentDateTime.toMSecsSinceEpoch());
    QString fileName = "config_" + timestamp + ".json";
    return fileName;
}

}
