#pragma once

#include <QObject>

#include "config_structures.h"

namespace config {

class ConfigObj : public QObject
{
    Q_OBJECT
public:
    explicit ConfigObj();

    void readFile(std::string jsonPath);
    void readFile(QString jsonPath);

    void addClashApi();

signals:
    void configUpdated();
    void errorOccured(QString text);

private:
    void writeDataToFile();

private:
    std::string m_jsonPath;
    std::string m_jsonBuffer;
    RootConfigUPtr m_rootConfig;
};

}
