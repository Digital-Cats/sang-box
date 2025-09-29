#pragma once

#include <QObject>
#include <QString>
#include <QVersionNumber>
#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QtGlobal>

#include <memory>

#include "proxy/core_updater.h"

class UpdaterViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString buildTime READ buildTime CONSTANT)
    Q_PROPERTY(QString compilerVersion READ compilerVersion CONSTANT)
    Q_PROPERTY(QString compilerId READ compilerId CONSTANT)
    Q_PROPERTY(QString coreVersion READ coreVersion NOTIFY coreVersionChanged)
    Q_PROPERTY(QString latestCoreVersion READ latestCoreVersion NOTIFY latestCoreVersionChanged)
    Q_PROPERTY(bool isCoreNewest READ isCoreNewest NOTIFY isCoreNewestChanged)
    Q_PROPERTY(bool updateAvailable READ updateAvailable NOTIFY updateAvailableChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(bool isCoreInstalled READ isCoreInstalled NOTIFY isCoreInstalledChanged)
    using CoreUpdaterUPtr = std::unique_ptr<CoreUpdater>;

public:
    explicit UpdaterViewModel();

    void setCoreVersion(QString version);

public slots:
    void requestLatestCoreVersion();
    void updateCore();

signals:
    void coreVersionChanged();
    void latestCoreVersionChanged();
    void isCoreNewestChanged();
    void updateAvailableChanged();
    void errorOccured(QString text);
    void busyChanged();
    void isCoreInstalledChanged();

private slots:
    void onCoreFetchFinished();
    void onCoreDownloadFinished(QString zipPath);

private:
    QString appVersion() const;
    QString qtVersion() const;
    QString buildTime() const;
    QString compilerVersion() const;
    QString compilerId() const;
    QString coreVersion() const;
    QString latestCoreVersion() const;
    bool isCoreNewest() const;
    bool updateAvailable();
    void setBusy(bool busy);
    bool busy() const;
    bool isCoreInstalled() const;

    bool extractZip(QString zipPath, QString distPath);

private:
    CoreUpdaterUPtr m_coreUpdater;
    QString m_coreVersion;
    QString m_latestCoreVersion;
    bool m_isCoreNewest;
    bool m_busy;
};
