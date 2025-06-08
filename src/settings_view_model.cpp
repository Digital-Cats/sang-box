#include "settings_view_model.h"

#include "settings/privilege_manager.h"
#include "task_scheduler.h"

SettingsViewModel::SettingsViewModel(QObject *parent)
    : QObject{parent}
    , m_settingsManager(std::make_unique<SettingsManager>(this))
{}

void SettingsViewModel::setupAutoRun(bool enabled)
{
    TaskScheduler taskScheduler;
    PrivilegeManager privilegeManager;

    m_settingsManager->setAutoRun(enabled);
    if (!isRunAsAdmin()) {
        // Not run as admin
        m_settingsManager->setAppAutoRun(enabled);
    } else {
        // Run as admin
        if (!(isAutoRun() ? taskScheduler.createTask() : taskScheduler.removeTask())) {
            // Refuse to create or remove the task
            m_settingsManager->setAutoRun(!enabled);
        }
    }
    emit isAutoRunChanged();
}

void SettingsViewModel::setupRunAsAdmin(bool enabled)
{
    TaskScheduler taskScheduler;
    PrivilegeManager privilegeManager;

    m_settingsManager->setRunAsAdmin(enabled);
    if (!isAutoRun()) {
        // Not run automatically
        privilegeManager.restartProgram();
    } else {
        // Run automatically
        m_settingsManager->setAppAutoRun(!enabled);
        if (isRunAsAdmin() ? taskScheduler.createTask() : taskScheduler.removeTask()) {
            // Create or remove the task successfully
            // privilegeManager.isRunningAsAdmin()
            privilegeManager.restartProgram();
        } else {
            // Refuse to create or remove the task
            m_settingsManager->setRunAsAdmin(!enabled);
        }
    }
    emit isRunAsAdminChanged();
}

bool SettingsViewModel::isAutoRun() const
{
    return m_settingsManager->autoRun();
}

bool SettingsViewModel::isRunAsAdmin() const
{
    return m_settingsManager->runAsAdmin();
}

QString SettingsViewModel::appVersion() const
{
    return QLatin1String(APP_VERSION);
}

QString SettingsViewModel::coreVersion() const
{
    return "1.10.0";
}
