#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <memory>

class CoreUpdater : public QObject
{
    Q_OBJECT

    using QNetworkAccessManagerUPtr = std::unique_ptr<QNetworkAccessManager>;

public:
    explicit CoreUpdater();

    void fetchLatest();

    void downloadLatest(QString savePath);

    QString latestVersion() const;
    QString assetName() const;
    QUrl assetUrl() const;

signals:
    void fetchFinished();
    void fetchError(QString text);

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished(QString zipPath);
    void downloadError(QString text);

private:
    void onFetchFinished();
    void onFetchError(QNetworkReply::NetworkError);

    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();
    void onDownloadError(QNetworkReply::NetworkError);

private:
    QNetworkAccessManagerUPtr m_manager;

    const QByteArray m_userAgent;
    const QUrl m_latestUrl;
    QNetworkReply *m_fetchReply;
    QNetworkReply *m_dlReply;

    QString m_latestVersion;
    QUrl m_assetUrl;
    QString m_assetName;
    QString m_savePath;
};
