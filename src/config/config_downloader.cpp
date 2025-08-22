#include "config_downloader.h"

#include <QObject>
#include <QDebug>

namespace config {

ConfigDownloader::ConfigDownloader(const QUrl &url)
    : m_manager(std::make_unique<QNetworkAccessManager>())
    , m_request(url)
    , m_reply(nullptr)
{
    m_request.setRawHeader("User-Agent", "sang-box");
    m_reply = m_manager->get(m_request);
    m_reply->ignoreSslErrors();
    QObject::connect(m_reply, &QNetworkReply::finished, this, &ConfigDownloader::finished);
    QObject::connect(m_reply, &QNetworkReply::errorOccurred,
                     this, &ConfigDownloader::errorOccurred);
    QObject::connect(m_reply, &QNetworkReply::errorOccurred,
                     this, &ConfigDownloader::onErrorOccurred);
    QObject::connect(m_reply, &QNetworkReply::downloadProgress, this, &ConfigDownloader::downloadProgress);
    connect(m_reply, &QNetworkReply::sslErrors,
            this, [](const QList<QSslError> &errors){ qDebug() << errors.empty(); });
}

bool ConfigDownloader::isFinished() const
{
    return m_reply->isFinished();
}

bool ConfigDownloader::isRunning() const
{
    return m_reply->isRunning();
}

QNetworkReply::NetworkError ConfigDownloader::error() const
{
    return m_reply->error();
}

QString ConfigDownloader::getConfig() const
{
    if (!isFinished())
        return {};
    QByteArray data = m_reply->readAll();
    return QString(data);
}

void ConfigDownloader::onErrorOccurred(QNetworkReply::NetworkError)
{
    emit errorOccurredText(m_reply->errorString());
}

}
