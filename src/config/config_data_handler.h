#pragma once

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
