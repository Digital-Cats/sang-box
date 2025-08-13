#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QObject>

#include "config_editor.h"

namespace config {

class Config;

class ConfigManager : public QObject
{
    Q_OBJECT

    using ConfigPtr = std::shared_ptr<Config>;
public:
    explicit ConfigManager(QObject *parent = nullptr);
    ~ConfigManager();

    void addConfig();
    void editConfig(int index);
    void importConfig();
    void removeConfig(int index);
    void switchConfig(int index);

    QStringList configNames() const;
    QString configFilePath() const;
    QString configName(int index) const;
    QString configName() const;
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
    void updateConfigList(int index, const QString &filePath, const QString &name);

private:
    // Read config list from registry
    void getConfigFromSettings();
    // Write config list to registry
    void saveConfigToSettings();

    int m_configIndex;
    QList<ConfigPtr> m_configList;
    ConfigEditor *m_configEditor;
};

}

#endif // CONFIG_MANAGER_H
