#pragma once

#include <QString>

class WindowsProxy
{
public:
    static void set(const QString &server, const QString &bypassList);
    static void clear();
    static bool isEnabled();
};
