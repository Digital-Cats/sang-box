#pragma once

#include <QAbstractItemModel>

#include "config/config_type.h"
#include "config_manager.h"

class ConfigListModel : public QAbstractItemModel
{
    Q_OBJECT

    using ConfigManagerPtr = std::shared_ptr<config::ConfigManager>;

    enum ConfigRoles {
        NameRole = Qt::UserRole + 1,
        SelectedRole,
        TypeRole,
    };

public:
    explicit ConfigListModel(ConfigManagerPtr configManager);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

public slots:
    void switchConfig(int index);
    void deleteConfig(int index);
    void importConfigData(config::ConfigType type, const QVariantMap &map);
    void updateRemoteConfig(int index);

signals:
    void errorOccured(QString text);

private slots:
    void processChanges(int index);
    void onBeginAddConfig();
    void onEndAddConfig();
    void updateCurrentConfigData();

private:
    QHash<int, QByteArray> roleNames() const override;

    ConfigManagerPtr m_configManager;
};
