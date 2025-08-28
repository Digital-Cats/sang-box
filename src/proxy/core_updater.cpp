#include "core_updater.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QFile>


CoreUpdater::CoreUpdater()
    : QObject()
    , m_manager(std::make_unique<QNetworkAccessManager>())
    , m_userAgent("sang-box")
    , m_latestUrl("https://api.github.com/repos/SagerNet/sing-box/releases/latest")
{
}

void CoreUpdater::fetchLatest()
{
    QNetworkRequest request(m_latestUrl);
    request.setRawHeader("User-Agent", m_userAgent);

    m_fetchReply = m_manager->get(request);

    connect(m_fetchReply, &QNetworkReply::finished, this, &CoreUpdater::onFetchFinished);
    connect(m_fetchReply, &QNetworkReply::errorOccurred, this, &CoreUpdater::onFetchError);
}

void CoreUpdater::onFetchFinished()
{
    QByteArray data = m_fetchReply->readAll();
    m_fetchReply->deleteLater();
    m_fetchReply = nullptr;

    const QJsonDocument doc = QJsonDocument::fromJson(data);
    const QJsonObject obj = doc.object();

    // Write version
    QString version = obj["tag_name"].toString();

    if (version.startsWith("v")) {
        version = version.mid(1);
    }

    m_latestVersion = version;

    // Write asset url
    m_assetUrl.clear();
    m_assetName.clear();
    const QJsonArray assets = obj["assets"].toArray();

    for (const auto& asset : assets)
    {
        const QJsonObject assetObj = asset.toObject();
        const QString name = assetObj["name"].toString();
        const QString url = assetObj["browser_download_url"].toString();

        if (name.contains("windows-amd64.zip"))
        {
            m_assetUrl = QUrl(url);
            m_assetName = name;
            break;
        }
    }

    if (m_latestVersion.isEmpty() or m_assetUrl.isEmpty())
    {
        emit fetchError(tr("Failed to fetch latest version"));
        return;
    }

    emit fetchFinished();
}

void CoreUpdater::onFetchError(QNetworkReply::NetworkError)
{
    emit fetchError(m_fetchReply->errorString());
}

void CoreUpdater::downloadLatest(QString savePath)
{
    if (m_assetUrl.isEmpty())
    {
        emit downloadError("Asset url is empty");
        return;
    }

    QNetworkRequest request(m_assetUrl);
    request.setRawHeader("User-Agent", m_userAgent);

    m_dlReply = m_manager->get(request);
    m_savePath = savePath;

    connect(m_dlReply, &QNetworkReply::downloadProgress, this, &CoreUpdater::onDownloadProgress);
    connect(m_dlReply, &QNetworkReply::finished, this, &CoreUpdater::onDownloadFinished);
    connect(m_dlReply, &QNetworkReply::errorOccurred, this, &CoreUpdater::onDownloadError);
}

void CoreUpdater::onDownloadProgress(qint64 received, qint64 total)
{
    emit downloadProgress(received, total);
}

void CoreUpdater::onDownloadFinished()
{
    QByteArray data = m_dlReply->readAll();
    m_dlReply->deleteLater();
    m_dlReply = nullptr;

    QFile file(m_savePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        emit downloadError(tr("Can't open file for writing: %1").arg(m_savePath));
        return;
    }

    file.write(data);
    file.close();
    emit downloadFinished(m_savePath);
}

void CoreUpdater::onDownloadError(QNetworkReply::NetworkError)
{
    emit fetchError(m_dlReply->errorString());
}

QString CoreUpdater::latestVersion() const
{
    return m_latestVersion;
}

QString CoreUpdater::assetName() const
{
    return m_assetName;
}

QUrl CoreUpdater::assetUrl() const
{
    return m_assetUrl;
}
