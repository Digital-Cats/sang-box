#include "main_window.h"
#include "main_window_new.h"
#include "tray_icon.h"

#define USE_WIDGETS 0

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

    QApplication::setQuitOnLastWindowClosed(false);
    QCoreApplication::setOrganizationName("NextIn");
    QCoreApplication::setApplicationName("qsing-box");

    QSharedMemory sharedMemory("qsing-box");
    if (!sharedMemory.create(1)) {
        QMessageBox::warning(nullptr, QMessageBox::tr("Warning"),
                             QMessageBox::tr("qsing-box is already running.")
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
        const QString baseName = "qsing-box_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    app.installTranslator(&translator);

#if USE_WIDGETS == 1
    MainWindow mainWindow;
    if (privilegeManager.isRunningAsAdmin()) {
        QString title = mainWindow.windowTitle() + QObject::tr(" (Administrator)");
        mainWindow.setWindowTitle(title);
    }
#else
    using MainWindowUPtr = std::unique_ptr<MainWindowNew>;
    using TrayIconUPtr = std::unique_ptr<TrayIcon>;

    MainWindowUPtr mainWindow = std::make_unique<MainWindowNew>();
    TrayIconUPtr trayIcon = std::make_unique<TrayIcon>();
    QObject::connect(trayIcon.get(), &TrayIcon::enableProxyActionTriggered,
                     mainWindow.get(), &MainWindowNew::startProxy);
    QObject::connect(trayIcon.get(), &TrayIcon::disableProxyActionTriggered,
                     mainWindow.get(), &MainWindowNew::stopProxy);
    QObject::connect(mainWindow.get(), &MainWindowNew::runningStateChanged,
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
#endif

    bool isAutorun = false;
    for (int i = 1; i < argc; ++i) {
        if (QString(argv[i]) == "/autorun") {
            isAutorun = true;
            break;
        }
    }
#if USE_WIDGETS == 1
    if (isAutorun) {
        QTimer::singleShot(3000, &mainWindow, &MainWindow::startProxy);
    } else {
        mainWindow.show();
    }
#else
    if (isAutorun) {
        QTimer::singleShot(3000, mainWindow.get(), &MainWindowNew::startProxy);
    } else {
        //mainWindow.show();
    }
#endif

    return app.exec();
}
