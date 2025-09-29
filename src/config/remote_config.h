#pragma once

#include <QUrl>

#include "config.h"

namespace config {

class RemoteConfig : public Config
{
public:
    explicit RemoteConfig(const QString &path, const QString &name,
                          bool isUpdatable, int updateInterval, const QUrl &url);
    ~RemoteConfig() = default;

    QUrl url() const;
    bool isUpdatable() const;
    int updateInterval() const;

    void setUrl(const QString &url);
    void setIsUpdatable(bool isUpdatable);
    void setUpdateInterval(int updateInterval);

    virtual ConfigType getType() const override { return ConfigType::Remote; };

private:
    QUrl m_url;
    bool m_isUpdatable;
    int m_updateInterval;
};

}
