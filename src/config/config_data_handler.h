#ifndef CONFIG_DATA_HANDLER_H
#define CONFIG_DATA_HANDLER_H

#include <QSettings>

namespace config {

class Config;
class RemoteConfig;

class ConfigDataHandler
{
    using ConfigPtr = std::shared_ptr<Config>;
    using RemoteConfigPtr = std::shared_ptr<RemoteConfig>;

public:
    static ConfigPtr loadConfig(QSettings &settings);
    static void saveConfig(QSettings &settings, ConfigPtr config);

protected:
    ConfigDataHandler() = default;
};

}

#endif // CONFIG_DATA_HANDLER_H
