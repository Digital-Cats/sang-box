#ifndef CORE_UPDATER_H
#define CORE_UPDATER_H

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

    void checkLatestVersion();

    bool isFinished() const;
    bool isRunning() const;

    QNetworkReply::NetworkError error() const;

    QString getLatestVersion() const;

signals:
    void finished();
    void errorOccurred(QNetworkReply::NetworkError code);
    void errorOccurredText(QString text);

private:
    void onErrorOccurred(QNetworkReply::NetworkError);

private:
    QNetworkAccessManagerUPtr m_manager;
    QNetworkRequest m_request;
    QNetworkReply *m_reply;
};

#endif // CORE_UPDATER_H
