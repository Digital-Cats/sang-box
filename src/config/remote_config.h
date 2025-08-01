#ifndef REMOTE_CONFIG_H
#define REMOTE_CONFIG_H

#include "config.h"

namespace config {

class RemoteConfig : public Config
{
public:
    explicit RemoteConfig(const QString &path, const QString &name,
                          bool isUpdatable, int updateInterval, const QString &url);
    ~RemoteConfig() = default;

    QString url() const;
    bool isUpdatable() const;
    int updateInterval() const;

    void setUrl(const QString &url);
    void setIsUpdatable(bool isUpdatable);
    void setUpdateInterval(int updateInterval);

    virtual ConfigType getType() const override { return ConfigType::Remote; };

private:
    QString m_url;
    bool m_isUpdatable;
    int m_updateInterval;
};

}

#endif // REMOTE_CONFIG_H
