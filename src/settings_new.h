#ifndef SETTINGS_NEW_H
#define SETTINGS_NEW_H

#include <QObject>
#include <QString>

#include <memory>

#include "settings/settings_manager.h"

class SettingsNew : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAutoRun READ isAutoRun NOTIFY isAutoRunChanged)
    Q_PROPERTY(bool isRunAsAdmin READ isRunAsAdmin NOTIFY isRunAsAdminChanged)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString coreVersion READ coreVersion CONSTANT)

    using SettingsManagerUPtr = std::unique_ptr<SettingsManager>;

public:
    explicit SettingsNew(QObject *parent = nullptr);

public slots:
    void setupAutoRun(bool enabled);
    void setupRunAsAdmin(bool enabled);

signals:
    void isAutoRunChanged();
    void isRunAsAdminChanged();

private:
    bool isAutoRun() const;
    bool isRunAsAdmin() const;
    QString appVersion() const;
    QString coreVersion() const;

private:
    SettingsManagerUPtr m_settingsManager;
};

#endif // SETTINGS_NEW_H
