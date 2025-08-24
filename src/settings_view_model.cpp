#include "settings_view_model.h"

SettingsViewModel::SettingsViewModel(QObject *parent)
    : QObject{parent}
    , m_settingsManager(std::make_unique<SettingsManager>(this))
{
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

