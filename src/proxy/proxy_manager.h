#ifndef PROXY_MANAGER_H
#define PROXY_MANAGER_H

#include <QObject>
#include <QProcess>

class ProxyManager : public QObject
{
    Q_OBJECT
public:
    explicit ProxyManager(QObject *parent = nullptr);

    void startProxy();
    void stopProxy();
    void clearSystemProxy();
    bool isSystemProxyEnabled() const;

    QByteArray readProxyProcessAllStandardError();
    int proxyProcessState() const;

    void setConfigFilePath(const QString &filePath);

    QString getCoreVersion() const;

signals:
    void proxyProcessStateChanged(int newState);
    void proxyProcessReadyReadStandardError();

private:
    bool programExist() const;

private:
    QProcess *m_proxyProcess = nullptr;
    QString m_configFilePath;
    QString m_program;
};

#endif // PROXY_MANAGER_H
