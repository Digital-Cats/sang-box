#pragma once

#include <QObject>

class PrivilegeManager : public QObject
{
    Q_OBJECT
public:
    explicit PrivilegeManager(QObject *parent = nullptr);

    bool isRunningAsAdmin();
    quint32 getLastError();

    bool runAsAdmin(const QString &programPath, const QString &parameters = "");
    void restartProgram();
};
