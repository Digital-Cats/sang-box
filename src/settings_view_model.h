#ifndef SETTINGS_NEW_H
#define SETTINGS_NEW_H

#include <QObject>
#include <QString>

#include <memory>

#include "settings/settings_manager.h"

class SettingsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAutoRun READ isAutoRun WRITE setupAutoRun NOTIFY isAutoRunChanged)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString coreVersion READ coreVersion NOTIFY coreVersionChanged)

    using SettingsManagerUPtr = std::unique_ptr<SettingsManager>;

public:
    explicit SettingsViewModel(QObject *parent = nullptr);

    void setCoreVersion(QString version);

public slots:
    void setupAutoRun(bool enabled);

signals:
    void isAutoRunChanged();
    void coreVersionChanged();

private:
    bool isAutoRun() const;
    QString appVersion() const;
    QString coreVersion() const;

private:
    SettingsManagerUPtr m_settingsManager;
    QString m_coreVersion;
};

#endif // SETTINGS_NEW_H
