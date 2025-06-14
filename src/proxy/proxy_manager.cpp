#include "proxy_manager.h"

#include <QCoreApplication>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>

#include "windows_proxy.h"

ProxyManager::ProxyManager(QObject *parent)
    : QObject{parent}
    , m_program(QCoreApplication::applicationDirPath() + "/sing-box.exe")
{
    m_proxyProcess = new QProcess(this);
}

void ProxyManager::startProxy()
{
    if (!programExist()) {
        QMessageBox::warning(nullptr, tr("Warning"),
                             tr("Can not find sing-box core!\n"
                                "Please place \"sing-box.exe\" in\n") + QCoreApplication::applicationDirPath()
                             );
    } else {
        if (m_configFilePath.isEmpty()) {
            QMessageBox::warning(nullptr, tr("Warning"),
                                 tr("The current configuration is empty!")
                                 );
        } else if (!QFile(m_configFilePath).exists()) {
            QMessageBox::warning(nullptr, tr("Warning"),
                                 tr("The current configuration is missing!")
                                 );
        } else {
            QStringList arguments;
            arguments << "run" << "-c" << m_configFilePath << "--disable-color" << "-D" << QCoreApplication::applicationDirPath();
            m_proxyProcess->start(m_program, arguments);
            connect(m_proxyProcess, &QProcess::stateChanged, this,
                    &ProxyManager::proxyProcessStateChanged);
            connect(m_proxyProcess, &QProcess::readyReadStandardError, this,
                    &ProxyManager::proxyProcessReadyReadStandardError);
            emit proxyProcessStateChanged(QProcess::Running);
        }
    }
}

void ProxyManager::stopProxy()
{
    if (m_proxyProcess->state() == QProcess::Running)
    {
        m_proxyProcess->kill();
        m_proxyProcess->waitForFinished();
    }
}

void ProxyManager::clearSystemProxy()
{
    WindowsProxy::clear();
}

bool ProxyManager::isSystemProxyEnabled() const
{
    return WindowsProxy::isEnabled();
}

QByteArray ProxyManager::readProxyProcessAllStandardError()
{
    return m_proxyProcess->readAllStandardError();
}

int ProxyManager::proxyProcessState() const
{
    return m_proxyProcess->state();
}

void ProxyManager::setConfigFilePath(const QString &filePath)
{
    m_configFilePath = filePath;
}

QString ProxyManager::getCoreVersion() const
{
    if (programExist())
    {
        QStringList arguments;
        arguments << "version";
        QProcess proxyProcessVersion;
        proxyProcessVersion.start(m_program, arguments);
        proxyProcessVersion.waitForFinished();
        QString versionLog = QString::fromUtf8(proxyProcessVersion.readAllStandardOutput());
        if (!versionLog.isEmpty())
        {
            return versionLog.split(QRegularExpression("\\s+")).at(2);
        }
    }
    return QString{};
}

bool ProxyManager::programExist() const
{
    return QFile::exists(m_program);
}
