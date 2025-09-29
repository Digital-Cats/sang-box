#pragma once

#include <QObject>

namespace config {

Q_NAMESPACE

enum class ConfigType {
    Local,
    Remote
};
Q_ENUM_NS(ConfigType)

}
