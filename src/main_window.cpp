#include "main_window.h"

#include <QDebug>
#include <QRegularExpression>

#include "html_color_text.h"

MainWindow::MainWindow(QObject *parent)
    : QObject{parent}
    , m_configManager(std::make_shared<ConfigManager>(this))
    , m_configListModel(std::make_shared<ConfigListModel>(m_configManager))
    , m_settings(std::make_shared<SettingsNew>(this))
    , m_proxyManager(std::make_unique<ProxyManager>(this))
{
    connect(m_configManager.get(), &ConfigManager::configChanged, this,
            &MainWindow::changeSelectedConfig);
    changeSelectedConfig();

    connect(m_proxyManager.get(), &ProxyManager::proxyProcessStateChanged,
            this, &MainWindow::runningStateChanged);
    connect(m_proxyManager.get(), &ProxyManager::proxyProcessReadyReadStandardError,
            this, &MainWindow::updateProxyOutput);
}

bool MainWindow::runnigState() const
{
    return m_proxyManager->proxyProcessState() == QProcess::Running;
}

void MainWindow::startProxy()
{
    m_proxyManager->startProxy();
}

void MainWindow::stopProxy()
{
    m_proxyManager->stopProxy();
}

ConfigListModel* MainWindow::configListModel() const
{
    return m_configListModel.get();
}

SettingsNew* MainWindow::settings() const
{
    return m_settings.get();
}

QString MainWindow::proxyOutput() const
{
    return m_proxyOutput;
}

void MainWindow::changeSelectedConfig()
{
    if (m_configManager->configCount() == 0)
    {
        if (m_proxyManager->proxyProcessState() == QProcess::Running)
        {
            stopProxy();
        }
    }
    else
    {
        m_proxyManager->setConfigFilePath(m_configManager->configFilePath());
        if (runnigState())
        {
            stopProxy();
            startProxy();
        }
    }
}

void MainWindow::updateProxyOutput()
{
    QByteArray outputData = m_proxyManager->readProxyProcessAllStandardError();
    QString outputText = QString::fromUtf8(outputData);
    if (outputText.isEmpty())
        return;
    HtmlColorText::appendHtmlColorText(outputText);

    QRegularExpression re("\\n$");
    QRegularExpressionMatch match = re.match(outputText);
    if (match.hasMatch())
    {
        const auto endPos = match.capturedStart(0);
        outputText = outputText.left(endPos);
    }
    if (!m_proxyOutput.isEmpty())
        m_proxyOutput += "<br>";
    m_proxyOutput += outputText;
    emit proxyOutputChanged();
}
