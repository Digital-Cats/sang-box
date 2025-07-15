#include "remote_config.h"

RemoteConfig::RemoteConfig(const QString &path, const QString &name,
    bool isUpdatable, int updateInterval, const QString &url)
    : Config(path, name)
    , m_url(url)
    , m_isUpdatable(isUpdatable)
    , m_updateInterval(updateInterval)
{

}

QString RemoteConfig::url() const
{
    return m_url;
}

bool RemoteConfig::isUpdatable() const
{
    return m_isUpdatable;
}

int RemoteConfig::updateInterval() const
{
    return m_updateInterval;
}

void RemoteConfig::setUrl(const QString &url)
{
    m_url = url;
}

void RemoteConfig::setIsUpdatable(bool isUpdatable)
{
    m_isUpdatable = isUpdatable;
}

void RemoteConfig::setUpdateInterval(int updateInterval)
{
    m_updateInterval = updateInterval;
}
