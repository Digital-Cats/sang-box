#include "config_data_handler.h"

#include "config.h"
#include "remote_config.h"
#include "config_type.h"

namespace config {

ConfigDataHandler::ConfigPtr ConfigDataHandler::loadConfig(QSettings &settings)
{
    ConfigType type =
        static_cast<ConfigType>(settings.value("type", static_cast<int>(ConfigType::Local))
                                    .toInt());

    ConfigPtr result = nullptr;
    QString filePath = settings.value("filePath").toString();
    QString name = settings.value("name").toString();

    switch (type) {
    case ConfigType::Local:
        result = std::make_shared<Config>(filePath, name);
        break;
    case ConfigType::Remote: {
        QString url = settings.value("url").toString();
        bool isUpdatable = settings.value("isUpdatable").toBool();
        int updateInterval = settings.value("updateInterval").toInt();
        result = std::make_shared<RemoteConfig>(filePath, name, isUpdatable, updateInterval, url);
        break;
    }
    default:
        break;
    }

    return result;
}

void ConfigDataHandler::saveConfig(QSettings &settings, ConfigPtr config)
{
    settings.setValue("type", static_cast<int>(config->getType()));
    settings.setValue("filePath", config->filePath());
    settings.setValue("name", config->name());

    switch (config->getType()) {
    case ConfigType::Remote: {
        auto remoteConfig = std::dynamic_pointer_cast<RemoteConfig>(config);
        settings.setValue("url", remoteConfig->url());
        settings.setValue("isUpdatable", remoteConfig->isUpdatable());
        settings.setValue("updateInterval", remoteConfig->updateInterval());
        break;
    }
    default:
        break;
    }
}

}
