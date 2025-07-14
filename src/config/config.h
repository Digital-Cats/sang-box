#ifndef CONFIG_H
#define CONFIG_H

#include "config_type.h"

#include <QString>
#include <QSettings>

class Config
{
    using ConfigPtr = std::shared_ptr<Config>;

public:
    explicit Config(const QString &path, const QString &name);
    ~Config() = default;

    QString filePath() const;
    QString name() const;

    void setFilePath(const QString &path);
    void setName(const QString &name);

    virtual ConfigType getType() const { return ConfigType::Local; };

private:
    QString m_filePath;
    QString m_name;
};

#endif // CONFIG_H
