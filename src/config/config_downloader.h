#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <memory>

namespace config {

class ConfigDownloader : public QObject
{
    Q_OBJECT

    using QNetworkAccessManagerUPtr = std::unique_ptr<QNetworkAccessManager>;
public:
    ConfigDownloader(const QUrl &url);

    bool isFinished() const;
    bool isRunning() const;

    QNetworkReply::NetworkError error() const;
    QString getConfig() const;

signals:
    void finished();
    void errorOccurred(QNetworkReply::NetworkError code);
    void errorOccurredText(QString text);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    void onErrorOccurred(QNetworkReply::NetworkError);

private:
    QNetworkAccessManagerUPtr m_manager;
    QNetworkRequest m_request;
    QNetworkReply *m_reply;
};

}
