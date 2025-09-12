#include "config_obj.h"

#include <glaze/glaze.hpp>

namespace config {

ConfigObj::ConfigObj()
    : QObject()
    , m_rootConfig(nullptr)
    , m_selectorOutbound(nullptr)
    , m_directOutbound(nullptr)
    , m_selectorRule(nullptr)
    , m_directRule(nullptr)
    , m_selectorProcessRule(nullptr)
{}

void ConfigObj::readFile(std::string jsonPath)
{
    reset();
    m_jsonPath = jsonPath;
    auto ec = glz::read_file_json<glz::opts{.error_on_unknown_keys = false, .raw_string = true}>(m_rootConfig, m_jsonPath, m_jsonBuffer);
    if (ec) {
        emit errorOccured(QString::fromStdString(glz::format_error(ec, m_jsonBuffer)));
        return;
    }
    findOrCreateCustomizableRules();
}

void ConfigObj::readFile(QString jsonPath)
{
    readFile(jsonPath.toStdString());
}

void ConfigObj::addClashApi()
{
    if (m_rootConfig->experimental == nullptr) {
        m_rootConfig->experimental = std::make_unique<experimental_t>();
    }
    if (m_rootConfig->experimental->clash_api == nullptr) {
        m_rootConfig->experimental->clash_api = std::make_unique<clash_api_t>();
    }

    /*
     * TODO: Introduce port logic:
     * 1) check port, which is in a config, it should be free
     * 2) if no port or current port is busy, find a new one and set it
     */
    m_rootConfig->experimental->clash_api->external_controller = "127.0.0.1:10814";
    writeDataToFile();
}

void ConfigObj::insertProcess(const std::string &process)
{
    if (m_selectorProcessRule)
        m_selectorProcessRule->insertProcess(process);
}

std::string ConfigObj::getProcess(size_t index) const
{
    if (m_selectorProcessRule)
        return m_selectorProcessRule->getProcess(index);
    return {};
}

void ConfigObj::eraseProcess(size_t index)
{
    if (m_selectorProcessRule)
        m_selectorProcessRule->eraseProcess(index);
}

void ConfigObj::insertDomain(const std::string &domain, OutboundType outboundType)
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        rule->insertDomain(domain);
}

std::string ConfigObj::getDomain(size_t index, OutboundType outboundType) const
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        return rule->getDomain(index);
    return {};
}

void ConfigObj::eraseDomain(size_t index, OutboundType outboundType)
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        rule->eraseDomain(index);
}

void ConfigObj::insertDomainSuffix(const std::string &domainSuffix, OutboundType outboundType)
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        rule->insertDomainSuffix(domainSuffix);
}

std::string ConfigObj::getDomainSuffix(size_t index, OutboundType outboundType) const
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        return rule->getDomainSuffix(index);
    return {};
}

void ConfigObj::eraseDomainSuffix(size_t index, OutboundType outboundType)
{
    RulePtr rule = getRule(outboundType);
    if (rule)
        rule->eraseDomainSuffix(index);
}

void ConfigObj::writeDataToFile()
{
    std::string outBuffer{};
    auto ec = glz::write_file_json<glz::opts{.prettify = true, .raw_string = true}>(m_rootConfig, m_jsonPath, outBuffer);
    if (ec) {
        emit errorOccured(QString::fromStdString(glz::format_error(ec, outBuffer)));
        return;
    }
}

void ConfigObj::findOrCreateCustomizableRules()
{
    for (auto &outbound : m_rootConfig->outbounds) {
        if (outbound->type == OutboundType::selector) {
            m_selectorOutbound = outbound;
        } else if (outbound->type == OutboundType::direct) {
            m_directOutbound = outbound;
        }

        if (m_selectorOutbound && m_directOutbound) {
            break;
        }
    }

    if (!m_directOutbound) {
        emit errorOccured("No direct outbound!");
        return;
    }

    if (!m_selectorOutbound) {
        emit errorOccured("No selector outbound!");
        return;
    }

    for (auto &rule : m_rootConfig->route.rules) {
        if (!rule->outbound)
            continue;

        if (*rule->outbound == m_selectorOutbound->tag && !rule->process_name) {
            m_selectorRule = rule;
        } else if (*rule->outbound == m_selectorOutbound->tag && rule->process_name) {
            m_selectorProcessRule = rule;
        } else if (*rule->outbound == m_directOutbound->tag) {
            m_directRule = rule;
        }

        if (m_selectorRule && m_directRule && m_selectorProcessRule) {
            break;
        }
    }

    if (!m_selectorRule) {
        createEmptyRule(m_selectorRule, m_selectorOutbound->tag);
        m_rootConfig->route.rules.emplace(m_rootConfig->route.rules.begin(), m_selectorRule);
    }

    if (!m_directRule) {
        createEmptyRule(m_directRule, m_directOutbound->tag);
        m_rootConfig->route.rules.emplace(m_rootConfig->route.rules.begin(), m_directRule);
    }

    if (!m_selectorProcessRule) {
        createEmptyRule(m_selectorProcessRule, m_selectorOutbound->tag);
        m_rootConfig->route.rules.push_back(m_selectorProcessRule);
    }
}

void ConfigObj::reset()
{
    m_jsonBuffer = {};

    m_selectorOutbound = nullptr;
    m_directOutbound = nullptr;

    m_selectorRule = nullptr;
    m_directRule = nullptr;
    m_selectorProcessRule = nullptr;

    m_rootConfig = std::make_unique<root_config_t>();
}

void ConfigObj::createEmptyRule(RulePtr &rule, const std::string &tag)
{
    rule = std::make_shared<rule_t>();
    rule->outbound = std::make_unique<std::string>(tag);
}

RulePtr ConfigObj::getRule(OutboundType outboundType) const
{
    RulePtr rule = nullptr;
    switch (outboundType) {
    case OutboundType::selector:
        rule = m_selectorRule;
        break;
    case OutboundType::direct:
        rule = m_directRule;
        break;
    default:
        break;
    }
    return rule;
}

}
