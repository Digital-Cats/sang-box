#include "config_structures.h"

namespace config {

void rule_t::insertStr(VectorStrPtr vectorStrPtr, const std::string &str)
{
    if (vectorStrPtr)
        vectorStrPtr->push_back(str);
}

std::string rule_t::getStr(VectorStrPtr vectorStrPtr, size_t index) const
{
    if (vectorStrPtr && vectorStrPtr->size() <= index)
        return vectorStrPtr->at(index);
    return {};
}

void rule_t::eraseStr(VectorStrPtr vectorStrPtr, size_t index)
{
     if (vectorStrPtr && vectorStrPtr->size() <= index)
        vectorStrPtr->erase(vectorStrPtr->begin() + index);
}

void rule_t::insertDomain(const std::string &domainStr)
{
    insertStr(domain, domainStr);
}

std::string rule_t::getDomain(size_t index) const
{
    return getStr(domain, index);
}

void rule_t::eraseDomain(size_t index)
{
    eraseStr(domain, index);
}

void rule_t::insertDomainSuffix(const std::string &domainSuffixStr)
{
    insertStr(domain_suffix, domainSuffixStr);
}

std::string rule_t::getDomainSuffix(size_t index) const
{
    return getStr(domain_suffix, index);
}

void rule_t::eraseDomainSuffix(size_t index)
{
    eraseStr(domain_suffix, index);
}

void rule_t::insertProcess(const std::string &processNameStr)
{
    insertStr(process_name, processNameStr);
}

std::string rule_t::getProcess(size_t index) const
{
    return getStr(process_name, index);
}

void rule_t::eraseProcess(size_t index)
{
    eraseStr(process_name, index);
}

}
