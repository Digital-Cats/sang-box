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

    void insertProcess(const std::string &process);
    std::string getProcess(size_t index) const;
    void eraseProcess(size_t index);

    void insertDomain(const std::string &domain, OutboundType outboundType);
    std::string getDomain(size_t index, OutboundType outboundType) const;
    void eraseDomain(size_t index, OutboundType outboundType);

    void insertDomainSuffix(const std::string &domainSuffix, OutboundType outboundType);
    std::string getDomainSuffix(size_t index, OutboundType outboundType) const;
    void eraseDomainSuffix(size_t index, OutboundType outboundType);

signals:
    void configUpdated();
    void errorOccured(QString text);

private:
    void writeDataToFile();
    void findOrCreateCustomizableRules();
    void reset();
    static void createEmptyRule(RulePtr &rule, const std::string &tag);
    RulePtr getRule(OutboundType outboundType) const;

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
