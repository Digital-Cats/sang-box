#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);

    QString lastOpenedFilePath();
    void setLastOpenedFilePath(const QString &filePath);

    int configIndex() const;
    void setConfigIndex(int index);

    bool autoRun() const;
    void setAutoRun(bool enabled);

private:
    QSettings m_iniSettings;
    QSettings m_nativeSettings;
};

#endif // SETTINGS_MANAGER_H
