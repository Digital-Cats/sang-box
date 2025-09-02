#include "config_manager.h"

#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include "config.h"
#include "config_io.h"
#include "config_downloader.h"
#include "remote_config.h"
#include "config_data_handler.h"
#include "settings_manager.h"

namespace {
const QString iniFile = config::ConfigIO::getConfigsFolder() + "/configList.ini";
}

namespace config {

ConfigManager::ConfigManager(QObject *parent)
    : QObject{parent}
{
    getConfigFromSettings();

    connect(this, &ConfigManager::endAddConfig, this, &ConfigManager::configUpdated);

    SettingsManager settingsManager;
    m_configIndex = settingsManager.configIndex();
}

void ConfigManager::addConfig(ConfigType type, const QVariantMap &map)
{
    switch (type) {
    case config::ConfigType::Local:
    {
        auto configIO = std::make_unique<config::ConfigIO>(map.value("filePath").toString());
        auto content = configIO->openConfigFile();
        configIO = std::make_unique<config::ConfigIO>();
        configIO->saveConfigFile(content);
        addLocalConfig(configIO->getConfigFilePath(), map.value("profileName").toString());
        break;
    }
    case config::ConfigType::Remote:
    {
        requestRemoteContent(map.value("urlPath").toUrl(), map.value("profileName").toString());
        break;
    }
    default:
        break;
    }

    if (m_configList.size() == 1) {
        switchConfig(0);
    }
}

void ConfigManager::removeConfig(int index)
{
    if (index >= 0 && index < m_configList.size()) {
        QString filePath = m_configList.at(index)->filePath();
        QFile(filePath).remove();
        m_configList.remove(index);
        saveConfigToSettings();
        int count = m_configList.count();
        // Already deleted, get new configuration quantity
        if (count != 0) {
            // The previous item is deleted,
            // and the selected configuration is moved forward by one item.
            if (index < m_configIndex) {
                switchConfig(m_configIndex - 1);
            }
            // Deleting the latter item,
            // have no impact on the selected configuration
            if (index > m_configIndex) {
            }
            // Delete the selected configuration,
            // need to switch to other configurations
            if (index == m_configIndex) {
                // The deleted item is not the last one
                if (index != count)
                {
                    switchConfig(m_configIndex);
                } else { // Deleted the last one
                    switchConfig(m_configIndex - 1);
                }
            }
        } else {
            // The configuration has been cleared,
            // need other operations
            emit configChanged();
        }
        emit configUpdated();
    }
}

void ConfigManager::switchConfig(int index)
{
    if (index >= 0 && index < m_configList.size()) {
        SettingsManager settingsManager;
        settingsManager.setConfigIndex(index);
        m_configIndex = index;

        emit configChanged();
    }
}

QStringList ConfigManager::configNames() const
{
    QStringList names;
    for (const auto &config : m_configList) {
        names.append(config->name());
    }
    return names;
}

QString ConfigManager::configFilePath() const
{
    if (!m_configList.isEmpty()){
        return m_configList.at(m_configIndex)->filePath();
    } else {
        return QString();
    }
}

QString ConfigManager::configName(int index) const
{
    if (index < 0 || index > m_configList.length())
        return QString();
    return m_configList.at(index)->name();
}

QString ConfigManager::configName() const
{
    if (!m_configList.isEmpty()){
        return m_configList.at(m_configIndex)->name();
    } else {
        return QString();
    }
}

ConfigType ConfigManager::configType(int index) const
{
    if (index < 0 || index > m_configList.length())
    //TODO: Should be None?
        return ConfigType::Local;
    return m_configList.at(index)->getType();
}

int ConfigManager::configIndex() const
{
    return m_configIndex;
}

int ConfigManager::configCount() const
{
    return m_configList.count();
}

void ConfigManager::deleteAllConfig()
{
    m_configList.clear();
    m_configIndex = 0;

    QString localPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QString directory = QString("%1/%2/config").arg(localPath, QCoreApplication::applicationName());
    QDir dir(directory);
    if (dir.exists()) {
        dir.removeRecursively();
    }

    SettingsManager settingsManager;
    settingsManager.setConfigIndex(m_configIndex);
    QSettings settings(iniFile, QSettings::IniFormat);
    settings.clear();

    emit configUpdated();
    emit configChanged();

}

void ConfigManager::updateRemoteConfig(int index)
{
    if (index >= 0 && index < m_configList.size()) {
        auto config = m_configList.at(index);
        if (auto remoteConfig = std::dynamic_pointer_cast<RemoteConfig>(config);
            config->getType() == ConfigType::Remote && remoteConfig != nullptr) {
            emit beginUpdateConfig(index);
            QUrl url = remoteConfig->url();
            auto configDownloader = std::make_shared<ConfigDownloader>(url);
            connect(configDownloader.get(), &ConfigDownloader::errorOccurredText,
                    this, &ConfigManager::networkError);
            connect(configDownloader.get(), &ConfigDownloader::finished,
                    this, [configDownloader, this, url, index, filePath = remoteConfig->filePath()](){
                auto content = configDownloader->getConfig();
                if (content.length() == 0)
                {
                    emit emptyConfigDownloaded();
                    return;
                }
                auto configIO = std::make_unique<ConfigIO>(filePath);
                configIO->saveConfigFile(content);
                emit endUpdateConfig(index);
            });
        }
    }
}

void ConfigManager::addLocalConfig(const QString &filePath, const QString &name)
{
    emit beginAddConfig();
    m_configList.append(std::make_shared<Config>(filePath, name));
    saveConfigToSettings();
    emit endAddConfig();
}

void ConfigManager::addRemoteConfig(const QString &filePath, const QUrl &url, const QString &name)
{
    emit beginAddConfig();
    auto remoteConfig = std::make_shared<RemoteConfig>(filePath, name, false, 0, url);
    auto config = std::static_pointer_cast<Config>(remoteConfig);
    m_configList.append(config);
    saveConfigToSettings();
    emit endAddConfig();
}

void ConfigManager::requestRemoteContent(QUrl url, QString name)
{
    emit beginDownloadNewConfig();
    auto configDownloader = std::make_shared<ConfigDownloader>(url);
    connect(configDownloader.get(), &ConfigDownloader::errorOccurredText,
            this, &ConfigManager::networkError);
    connect(configDownloader.get(), &ConfigDownloader::finished,
            this, [configDownloader, this, url, name](){
        auto content = configDownloader->getConfig();
        if (content.length() == 0)
        {
            emit emptyConfigDownloaded();
            return;
        }
        auto configIO = std::make_unique<ConfigIO>();
        configIO->saveConfigFile(content);
        addRemoteConfig(configIO->getConfigFilePath(), url, name);
        emit endDownloadNewConfig();
    });
}

void ConfigManager::getConfigFromSettings()
{
    QSettings settings(iniFile, QSettings::IniFormat);
    int size = settings.beginReadArray("Config");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        auto config = ConfigDataHandler::loadConfig(settings);
        if (config) {
            m_configList.append(config);
        } else {
            emit configsLoadError();
        }
    }
    settings.endArray();

    emit configUpdated();
}

void ConfigManager::saveConfigToSettings()
{
    QSettings settings(iniFile, QSettings::IniFormat);
    settings.beginWriteArray("Config");
    settings.remove("");
    for (int i = 0; i < m_configList.size(); ++i) {
        settings.setArrayIndex(i);
        ConfigDataHandler::saveConfig(settings, m_configList.at(i));
    }
    settings.endArray();
}

}
