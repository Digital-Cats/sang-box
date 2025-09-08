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
    void findOrCreateCustomizableRules();
    void reset();
    static void createEmptyRule(RulePtr &rule, const std::string &tag);

private:
    std::string m_jsonPath;
    std::string m_jsonBuffer;
    RootConfigUPtr m_rootConfig;

    OutboundPtr m_selectorOutbound;
    OutboundPtr m_directOutbound;

    RulePtr m_selectorRule;
    RulePtr m_directRule;
    RulePtr m_selectorProcessRule;
};

}
