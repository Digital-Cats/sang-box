#include "settings_view_model.h"

SettingsViewModel::SettingsViewModel(QObject *parent)
    : QObject{parent}
    , m_settingsManager(std::make_unique<SettingsManager>(this))
{}

void SettingsViewModel::setCoreVersion(QString version)
{
    if (version.isEmpty())
        m_coreVersion = QObject::tr("Not installed");
    else
        m_coreVersion = version;
    emit coreVersionChanged();
}

void SettingsViewModel::setupAutoRun(bool enabled)
{
    m_settingsManager->setAutoRun(enabled);
    emit isAutoRunChanged();
}

bool SettingsViewModel::isAutoRun() const
{
    return m_settingsManager->autoRun();
}

QString SettingsViewModel::appVersion() const
{
    return QLatin1String(PROJECT_VERSION);
}

QString SettingsViewModel::coreVersion() const
{
    return m_coreVersion;
}
