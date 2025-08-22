#include "settings_view_model.h"

SettingsViewModel::SettingsViewModel(QObject *parent)
    : QObject{parent}
    , m_settingsManager(std::make_unique<SettingsManager>(this))
    , m_coreUpdater(std::make_unique<CoreUpdater>())
{
    connect(m_coreUpdater.get(), &CoreUpdater::finished,
            this, &SettingsViewModel::latestCoreVersionChanged);
    connect(m_coreUpdater.get(), &CoreUpdater::errorOccurredText,
            this, [this](QString text){
        emit errorOccurred(QObject::tr("Core update failed! %1").arg(text));
    });
}

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

void SettingsViewModel::requestLatestCoreVersion()
{
    m_coreUpdater->checkLatestVersion();
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

QString SettingsViewModel::latestCoreVersion() const
{
    return m_coreUpdater->getLatestVersion();
}

