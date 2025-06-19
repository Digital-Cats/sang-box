#include "settings_manager.h"

#include <QCoreApplication>
#include <QDir>
#include <QSettings>

namespace
{
static const QString autoRunReg = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
{}

QString SettingsManager::lastOpenedFilePath()
{
    QSettings settings;
    return settings.value("lastOpenedFilePath").toString();
}

void SettingsManager::setLastOpenedFilePath(const QString &filePath)
{
    QSettings settings;
    settings.setValue("lastOpenedFilePath", filePath);
}

int SettingsManager::configIndex() const
{
    QSettings settings;
    return settings.value("configIndex").toInt();
}

void SettingsManager::setConfigIndex(int index)
{
    QSettings settings;
    settings.setValue("configIndex", index);
}

bool SettingsManager::autoRun() const
{
    QSettings settings(autoRunReg, QSettings::NativeFormat);
    return settings.contains(QCoreApplication::applicationName());
}

void SettingsManager::setAutoRun(bool enabled)
{
    QString appName = QCoreApplication::applicationName();
    QString appPath = QCoreApplication::applicationFilePath();
    QSettings settings(autoRunReg, QSettings::NativeFormat);

    if (enabled) {
        settings.setValue(appName, "\"" + QDir::toNativeSeparators(appPath) + "\" /autorun");
    } else {
        settings.remove(appName);
    }
}

void SettingsManager::removeConfig()
{
    QSettings settings;
    settings.beginWriteArray("Config");
    settings.remove("");
    settings.endArray();
}

void SettingsManager::clearAllSettings()
{
    QSettings settings;
    settings.clear();
}
