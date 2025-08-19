#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QObject>
#include "config_type.h"

namespace config {

class Config;

class ConfigManager : public QObject
{
    Q_OBJECT

    using ConfigPtr = std::shared_ptr<Config>;
public:
    explicit ConfigManager(QObject *parent = nullptr);
    ~ConfigManager() = default;

    void removeConfig(int index);
    void switchConfig(int index);

    QStringList configNames() const;
    QString configFilePath() const;
    QString configName(int index) const;
    QString configName() const;
    ConfigType configType(int index) const;
    int configIndex() const;
    int configCount() const;

    void deleteAllConfig();

signals:
    void configUpdated();
    void configChanged();
    void configRenamed(int index);
    void beginAddConfig();
    void endAddConfig();
    void configLoadError();

public slots:
    void appendConfigList(const QString &filePath, const QString &name);
    void appendConfigListRemote(const QString &filePath, const QUrl &url, const QString &name);

private:
    // Read config list from registry
    void getConfigFromSettings();
    // Write config list to registry
    void saveConfigToSettings();

    int m_configIndex;
    QList<ConfigPtr> m_configList;
};

}

#endif // CONFIG_MANAGER_H
