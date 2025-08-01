#ifndef CONFIG_TYPE_H
#define CONFIG_TYPE_H

#include <QObject>

namespace config {

Q_NAMESPACE

enum class ConfigType {
    Local,
    Remote
};
Q_ENUM_NS(ConfigType)

}

#endif // CONFIG_TYPE_H
