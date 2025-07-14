#ifndef CONFIG_DATA_HANDLER_H
#define CONFIG_DATA_HANDLER_H

#include "config.h"

#include <QSettings>

class ConfigDataHandler
{
    using ConfigPtr = std::shared_ptr<Config>;

public:
    static ConfigPtr loadConfig(QSettings &settings);
    static void saveConfig(QSettings &settings, ConfigPtr config);

protected:
    ConfigDataHandler() = default;
};

#endif // CONFIG_DATA_HANDLER_H
