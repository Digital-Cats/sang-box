#include "updater_view_model.h"

UpdaterViewModel::UpdaterViewModel()
    : QObject()
    , m_coreUpdater(std::make_unique<CoreUpdater>())
{
    connect(m_coreUpdater.get(), &CoreUpdater::finished,
            this, &UpdaterViewModel::latestCoreVersionChanged);
    connect(m_coreUpdater.get(), &CoreUpdater::errorOccurredText,
            this, [this](QString text){
                emit errorOccured(QObject::tr("Core update failed! %1").arg(text));
    });
}

void UpdaterViewModel::setCoreVersion(QString version)
{
    if (version.isEmpty())
        m_coreVersion = QObject::tr("Not installed");
    else
        m_coreVersion = version;
    emit coreVersionChanged();
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
