#include "updater_view_model.h"

UpdaterViewModel::UpdaterViewModel()
    : QObject()
    , m_coreUpdater(std::make_unique<CoreUpdater>())
    , m_isCoreNewest(false)
    , m_busy(false)
{
    connect(m_coreUpdater.get(), &CoreUpdater::fetchFinished,
            this, &UpdaterViewModel::onCoreFetchFinished);
    connect(m_coreUpdater.get(), &CoreUpdater::downloadFinished,
            this, &UpdaterViewModel::onCoreDownloadFinished);

    connect(m_coreUpdater.get(), &CoreUpdater::fetchError,
            this, [this](QString text){
                emit errorOccured(QObject::tr("Core fetch failed! %1").arg(text));
    });
    connect(m_coreUpdater.get(), &CoreUpdater::downloadError,
            this, [this](QString text){
                emit errorOccured(QObject::tr("Core download failed! %1").arg(text));
            });

    connect(m_coreUpdater.get(), &CoreUpdater::downloadError,
            this, [this](QString){
                setBusy(false);
            });
}

void UpdaterViewModel::setCoreVersion(QString version)
{
    m_coreVersion = version.isEmpty() ? QObject::tr("Not installed") : version;
    emit coreVersionChanged();
}

void UpdaterViewModel::requestLatestCoreVersion()
{
    m_coreUpdater->fetchLatest();
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
    return m_coreUpdater->latestVersion();
}

bool UpdaterViewModel::isCoreNewest() const
{
    return m_isCoreNewest;
}

void UpdaterViewModel::onCoreFetchFinished()
{
    m_latestCoreVersion = m_coreUpdater->latestVersion();
    emit latestCoreVersionChanged();

    const auto currentVersion = QVersionNumber::fromString(m_coreVersion);
    const auto latestVersion = QVersionNumber::fromString(m_coreUpdater->latestVersion());
    const bool isCoreNewest = (!currentVersion.isNull() && !latestVersion.isNull() &&
                               QVersionNumber::compare(currentVersion, latestVersion) >= 0);

    if (m_isCoreNewest != isCoreNewest) {
        m_isCoreNewest = isCoreNewest;
        emit isCoreNewestChanged();
        emit updateAvailableChanged();
    }
}

void UpdaterViewModel::updateCore()
{
    setBusy(true);
    const QString savePath = QCoreApplication::applicationDirPath() + "/" + m_coreUpdater->assetName();
    m_coreUpdater->downloadLatest(savePath);
}

void UpdaterViewModel::onCoreDownloadFinished(QString zipPath)
{
    const QString tmpDist = QCoreApplication::applicationDirPath() + "/tmp";
    QDir().mkpath(tmpDist);

    if (!extractZip(zipPath, tmpDist)) {
        emit errorOccured(tr("Failed to extract archive."));
        return;
    }

    const QString zipName = QFileInfo(m_coreUpdater->assetName()).completeBaseName();
    const QString exe = tmpDist + "/" + zipName + "/sing-box.exe";
    const QString distExe = QCoreApplication::applicationDirPath() + "/sing-box.exe";

    if (QFile::exists(distExe))
    {
        QFile::remove(distExe);
    }

    if (!QFile::copy(exe, distExe))
    {
        emit errorOccured("Failed to replace core");
        return;
    }

    m_coreVersion = m_latestCoreVersion;
    emit coreVersionChanged();

    QFile::remove(zipPath);
    QDir(tmpDist).removeRecursively();

    m_isCoreNewest = true;
    emit isCoreNewestChanged();
    emit updateAvailableChanged();
    setBusy(false);
}

bool UpdaterViewModel::extractZip(QString zipPath, QString distPath)
{
    QProcess ps;
    QString cmd = "powershell";
    QString command = QString("Expand-Archive "
                              "-LiteralPath \"%1\" "
                              "-DestinationPath \"%2\" "
                              "-Force")
                          .arg(zipPath, distPath);

    ps.start(cmd, {"-NoProfile", "-Command", command});
    ps.waitForFinished(-1);
    return ps.exitStatus() == QProcess::NormalExit && ps.exitCode() == 0;
}


bool UpdaterViewModel::updateAvailable()
{
    return !m_isCoreNewest && !m_latestCoreVersion.isEmpty();
}

bool UpdaterViewModel::busy() const
{
    return m_busy;
}

void UpdaterViewModel::setBusy(bool busy)
{
    m_busy = busy;
    emit busyChanged();
}
