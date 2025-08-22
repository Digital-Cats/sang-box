#include "settings_manager.h"

#include <QCoreApplication>
#include <QDir>

SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
    , m_iniSettings("./settings.ini", QSettings::IniFormat)
    , m_nativeSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat)
{}

QString SettingsManager::lastOpenedFilePath()
{
    return m_iniSettings.value("lastOpenedFilePath").toString();
}

void SettingsManager::setLastOpenedFilePath(const QString &filePath)
{
    m_iniSettings.setValue("lastOpenedFilePath", filePath);
}

int SettingsManager::configIndex() const
{
    return m_iniSettings.value("configIndex").toInt();
}

void SettingsManager::setConfigIndex(int index)
{
    m_iniSettings.setValue("configIndex", index);
}

bool SettingsManager::autoRun() const
{
    return m_nativeSettings.contains(QCoreApplication::applicationName());
}

void SettingsManager::setAutoRun(bool enabled)
{
    QString appName = QCoreApplication::applicationName();
    QString appPath = QCoreApplication::applicationFilePath();

    if (enabled) {
        m_nativeSettings.setValue(appName, "\"" + QDir::toNativeSeparators(appPath) + "\" /autorun");
    } else {
        m_nativeSettings.remove(appName);
    }
}
