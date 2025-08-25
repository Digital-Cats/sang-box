#ifndef UPDATER_VIEW_MODEL_H
#define UPDATER_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <QVersionNumber>

#include <memory>

#include "proxy/core_updater.h"

class UpdaterViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString coreVersion READ coreVersion NOTIFY coreVersionChanged)
    Q_PROPERTY(QString latestCoreVersion READ latestCoreVersion NOTIFY latestCoreVersionChanged)
    Q_PROPERTY(bool isCoreNewest READ isCoreNewest NOTIFY isCoreNewestChanged)

    using CoreUpdaterUPtr = std::unique_ptr<CoreUpdater>;

public:
    explicit UpdaterViewModel();

    void setCoreVersion(QString version);

public slots:
    void requestLatestCoreVersion();

signals:
    void coreVersionChanged();
    void latestCoreVersionChanged();
    void isCoreNewestChanged();

    void errorOccured(QString text);

private slots:
    void onCoreCheckFinished();

private:
    QString appVersion() const;
    QString coreVersion() const;
    QString latestCoreVersion() const;
    bool isCoreNewest() const;

private:
    CoreUpdaterUPtr m_coreUpdater;
    QString m_coreVersion;
    bool m_isCoreNewest = true;
};

#endif // UPDATER_VIEW_MODEL_H
