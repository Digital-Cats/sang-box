#include "updater_view_model.h"

UpdaterViewModel::UpdaterViewModel()
    : QObject()
    , m_coreUpdater(std::make_unique<CoreUpdater>())
{
    connect(m_coreUpdater.get(), &CoreUpdater::finished,
            this, &UpdaterViewModel::onCoreCheckFinished);

    connect(m_coreUpdater.get(), &CoreUpdater::errorOccurredText,
            this, [this](QString text){
                emit errorOccured(QObject::tr("Core update failed! %1").arg(text));
    });
}

void UpdaterViewModel::setCoreVersion(QString version)
{
    m_coreVersion = version.isEmpty() ? QObject::tr("Not installed") : version;
    emit coreVersionChanged();

    // const auto currentVersion = QVersionNumber::fromString(m_coreVersion);
    // const auto latestVersion = QVersionNumber::fromString(m_coreUpdater->getLatestVersion());
    // const bool isCoreNewest = (!currentVersion.isNull() && !latestVersion.isNull() &&
    //                             QVersionNumber::compare(currentVersion, latestVersion) >= 0);

    // if (m_isCoreNewest != isCoreNewest) {
    //     m_isCoreNewest = isCoreNewest;
    //     emit isCoreNewestChanged();
    // }
}

void UpdaterViewModel::requestLatestCoreVersion()
{
    m_coreUpdater->checkLatestVersion();
}

QString UpdaterViewModel::appVersion() const
{
    return QLatin1String(PROJECT_VERSION);
}

QString UpdaterViewModel::coreVersion() const
{
    return m_coreVersion;
}

QString UpdaterViewModel::latestCoreVersion() const
{
    return m_coreUpdater->getLatestVersion();
}

bool UpdaterViewModel::isCoreNewest() const
{
    return m_isCoreNewest;
}

void UpdaterViewModel::onCoreCheckFinished()
{
    emit latestCoreVersionChanged();

    const auto currentVersion = QVersionNumber::fromString(m_coreVersion);
    const auto latestVersion = QVersionNumber::fromString(m_coreUpdater->getLatestVersion());
    const bool isCoreNewest = (!currentVersion.isNull() && !latestVersion.isNull() &&
                               QVersionNumber::compare(currentVersion, latestVersion) >= 0);

    if (m_isCoreNewest != isCoreNewest) {
        m_isCoreNewest = isCoreNewest;
        emit isCoreNewestChanged();
    }
}
