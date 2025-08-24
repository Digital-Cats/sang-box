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

    using SettingsManagerUPtr = std::unique_ptr<SettingsManager>;

public:
    explicit SettingsViewModel(QObject *parent = nullptr);

public slots:
    void setupAutoRun(bool enabled);

signals:
    void isAutoRunChanged();

private:
    bool isAutoRun() const;

private:
    SettingsManagerUPtr m_settingsManager;
};

#endif // SETTINGS_NEW_H
