#ifndef SETTINGS_NEW_H
#define SETTINGS_NEW_H

#include <QObject>
#include <QString>

#include <memory>

#include "settings/settings_manager.h"
#include "proxy/core_updater.h"

class SettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAutoRun READ isAutoRun WRITE setupAutoRun NOTIFY isAutoRunChanged)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString coreVersion READ coreVersion NOTIFY coreVersionChanged)
    Q_PROPERTY(QString latestCoreVersion READ latestCoreVersion NOTIFY latestCoreVersionChanged)

    using SettingsManagerUPtr = std::unique_ptr<SettingsManager>;
    using CoreUpdaterUPtr = std::unique_ptr<CoreUpdater>;

public:
    explicit SettingsViewModel(QObject *parent = nullptr);

    void setCoreVersion(QString version);

public slots:
    void setupAutoRun(bool enabled);
    void requestLatestCoreVersion();

signals:
    void isAutoRunChanged();
    void coreVersionChanged();
    void latestCoreVersionChanged();

private:
    bool isAutoRun() const;
    QString appVersion() const;
    QString coreVersion() const;
    QString latestCoreVersion() const;

private:
    SettingsManagerUPtr m_settingsManager;
    CoreUpdaterUPtr m_coreUpdater;
    QString m_coreVersion;
};

#endif // SETTINGS_NEW_H
