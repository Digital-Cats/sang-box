#include "config_data_handler.h"

#include "config_type.h"

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
    case ConfigType::Remote:

        break;
    default:
        break;
    }
}
