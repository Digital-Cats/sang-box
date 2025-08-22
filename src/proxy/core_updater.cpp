#include "core_updater.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


CoreUpdater::CoreUpdater()
    : QObject()
    , m_manager(std::make_unique<QNetworkAccessManager>())
    , m_request(QUrl("https://api.github.com/repos/SagerNet/sing-box/releases/latest"))
    , m_reply(nullptr)
{
    m_request.setRawHeader("User-Agent", "sang-box");
}

void CoreUpdater::checkLatestVersion()
{
    m_reply = m_manager->get(m_request);

    connect(m_reply, &QNetworkReply::finished, this, &CoreUpdater::finished);
    connect(m_reply, &QNetworkReply::errorOccurred, this, &CoreUpdater::errorOccurred);
    connect(m_reply, &QNetworkReply::errorOccurred, this, &CoreUpdater::onErrorOccurred);
}

bool CoreUpdater::isFinished() const
{
    if (m_reply != nullptr)
        return m_reply->isFinished();
    return false;
}

bool CoreUpdater::isRunning() const
{
    if (m_reply != nullptr)
        return m_reply->isRunning();
    return false;
}

QNetworkReply::NetworkError CoreUpdater::error() const
{
    return m_reply->error();
}

QString CoreUpdater::getLatestVersion() const
{
    if (!isFinished() || !m_reply)
        return QString();

    QByteArray data = m_reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString version = obj["tag_name"].toString();

    if (version.startsWith("v")) {
        version = version.mid(1);
    }

    return version;
}

void CoreUpdater::onErrorOccurred(QNetworkReply::NetworkError)
{
    emit errorOccurredText(m_reply->errorString());
}
