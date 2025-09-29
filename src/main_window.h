#pragma once

#include <QObject>
#include <QProcess>

#include <memory>

#include "config_manager.h"
#include "proxy_manager.h"
#include "config_list_model.h"
#include "settings_view_model.h"
#include "updater_view_model.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConfigListModel* configListModel READ configListModel NOTIFY configListModelChanged)
    Q_PROPERTY(SettingsViewModel* settings READ settings NOTIFY settingsChanged)
    Q_PROPERTY(UpdaterViewModel* updater READ updater NOTIFY updaterChanged)
    Q_PROPERTY(bool runnigState READ runnigState NOTIFY runningStateChanged)
    Q_PROPERTY(QString proxyOutput READ proxyOutput NOTIFY proxyOutputChanged)

    using ConfigManagerPtr = std::shared_ptr<config::ConfigManager>;
    using ConfigListModelPtr = std::shared_ptr<ConfigListModel>;
    using SettingsPtr = std::shared_ptr<SettingsViewModel>;
    using UpdaterPtr = std::shared_ptr<UpdaterViewModel>;
    using ProxyManagerUPtr = std::unique_ptr<ProxyManager>;

public:
    explicit MainWindow(QObject *parent = nullptr);

    bool runnigState() const;

public slots:
    void startProxy();
    void stopProxy();

signals:
    void configListModelChanged();
    void settingsChanged();
    void updaterChanged();
    void runningStateChanged();
    void proxyOutputChanged();
    void errorOccured(QString text);

private:
    ConfigListModel* configListModel() const;
    SettingsViewModel* settings() const;
    UpdaterViewModel* updater() const;
    QString proxyOutput() const;

private slots:
    void changeSelectedConfig();
    void updateProxyOutput();

private:
    ConfigManagerPtr m_configManager;
    ConfigListModelPtr m_configListModel;
    SettingsPtr m_settings;
    UpdaterPtr m_updater;
    ProxyManagerUPtr m_proxyManager;
    QString m_proxyOutput;
};
