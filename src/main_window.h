#ifndef MAIN_WINDOW_NEW_H
#define MAIN_WINDOW_NEW_H

#include <QObject>
#include <QProcess>

#include <memory>

#include "config_manager.h"
#include "proxy_manager.h"
#include "config_list_model.h"
#include "settings_view_model.h"

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConfigListModel* configListModel READ configListModel NOTIFY configListModelChanged)
    Q_PROPERTY(SettingsViewModel* settings READ settings NOTIFY settingsChanged)
    Q_PROPERTY(bool runnigState READ runnigState NOTIFY runningStateChanged)
    Q_PROPERTY(QString proxyOutput READ proxyOutput NOTIFY proxyOutputChanged)

    using ConfigManagerPtr = std::shared_ptr<ConfigManager>;
    using ConfigListModelPtr = std::shared_ptr<ConfigListModel>;
    using SettingsPtr = std::shared_ptr<SettingsViewModel>;
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
    void runningStateChanged();
    void proxyOutputChanged();

private:
    ConfigListModel* configListModel() const;
    SettingsViewModel* settings() const;
    QString proxyOutput() const;

private slots:
    void changeSelectedConfig();
    void updateProxyOutput();

private:
    ConfigManagerPtr m_configManager;
    ConfigListModelPtr m_configListModel;
    SettingsPtr m_settings;
    ProxyManagerUPtr m_proxyManager;
    QString m_proxyOutput;
};

#endif // MAIN_WINDOW_NEW_H
