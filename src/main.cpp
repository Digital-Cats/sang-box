#include "main_window.h"
#include "tray_icon.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QMessageBox>
#include <QSharedMemory>
#include <QTimer>
#include <QTranslator>

#include <Windows.h>

#include "privilege_manager.h"
#include "settings_manager.h"
#include <QtQml/QQmlExtensionPlugin>
Q_IMPORT_QML_PLUGIN(Qcm_MaterialPlugin)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle("fusion");
    QApplication::setQuitOnLastWindowClosed(false);
    QCoreApplication::setOrganizationName("R2 team");
    QCoreApplication::setApplicationName("sang-box");

    QSharedMemory sharedMemory("sang-box");
    if (!sharedMemory.create(1)) {
        QMessageBox::warning(nullptr, QMessageBox::tr("Warning"),
                             QMessageBox::tr("sang-box is already running.")
                             );
        return 1;
    }

    PrivilegeManager privilegeManager;
    SettingsManager settingsManager;
    if (settingsManager.runAsAdmin() && !privilegeManager.isRunningAsAdmin()) {
        QString appPath = QCoreApplication::applicationFilePath();

        if (!privilegeManager.runAsAdmin(appPath)) {
            if (privilegeManager.getLastError() == ERROR_CANCELLED) {
                // Rejected UAC prompt
                qDebug() << "Administrator permissions were denied.\n";
            } else {
                // Other errors cause privilege elevation to fail
                qDebug() << "Failed to launch as administrator.\n";
            }
        } else {
            // Successfully started administrator mode
            // and exited the current instance
            return 0;
        }
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    app.installTranslator(&translator);

    using MainWindowUPtr = std::unique_ptr<MainWindow>;
    using TrayIconUPtr = std::unique_ptr<TrayIcon>;

    MainWindowUPtr mainWindow = std::make_unique<MainWindow>();
    TrayIconUPtr trayIcon = std::make_unique<TrayIcon>();
    QObject::connect(trayIcon.get(), &TrayIcon::enableProxyActionTriggered,
                     mainWindow.get(), &MainWindow::startProxy);
    QObject::connect(trayIcon.get(), &TrayIcon::disableProxyActionTriggered,
                     mainWindow.get(), &MainWindow::stopProxy);
    QObject::connect(mainWindow.get(), &MainWindow::runningStateChanged,
                     trayIcon.get(), [&mainWindow, &trayIcon]()
                     {
                         trayIcon->setMenuEnabled(mainWindow->runnigState());
                         trayIcon->setIconState(mainWindow->runnigState());
                     });
    trayIcon->show();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("mainWindow", mainWindow.get());
    engine.rootContext()->setContextProperty("trayIcon", trayIcon.get());
    engine.addImportPath("qrc:/");

    engine.loadFromModule("QSingBox", "Main");

    bool isAutorun = false;
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "/autorun") {
            isAutorun = true;
            break;
        }
    }
    if (isAutorun) {
        QTimer::singleShot(3000, mainWindow.get(), &MainWindow::startProxy);
    } else {
        //mainWindow.show();
    }

    return app.exec();
}
