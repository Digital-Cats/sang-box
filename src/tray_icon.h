#pragma once

#include <QObject>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QAction;
class QMainWindow;
QT_END_NAMESPACE

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);
    ~TrayIcon();

    void show();
    void setIcon(const QIcon &icon);
    bool isVisible() const;

public slots:
    // According to the status of proxy,
    // uses to enable of disable the action of trayIconMenu
    void setMenuEnabled(bool proxy_enabled);
    void setIconState(bool proxy_enabled);

signals:
    // Notify the main window that the system tray menu was clicked,
    // to change the status or display of proxy
    void enableProxyActionTriggered();
    void disableProxyActionTriggered();
    void restoreActionTriggered();
    void openWindowTriggered();

private:
    void createAction();
    void createTrayIcon();

private slots:
    void processActivated(int reason);

private:
    // Action for creating the menu of system tray
    QAction *m_enableProxyAction;
    QAction *m_disableProxyAction;
    QAction *m_restoreAction;
    QAction *m_quitAction;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;
};
