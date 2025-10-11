#include "preset.h"

namespace preset {

Preset::Preset(std::string name, std::filesystem::path configFolder)
    : m_data(std::make_unique<preset_data_t>())
{
    m_data->name = name;
    m_path = configFolder / name;
    m_path.replace_extension(".json");
}

Preset::Preset(std::filesystem::path path)
    : m_data(std::make_unique<preset_data_t>())
    , m_path(path)
{

}

VectorStr Preset::getProcesses() const
{
    return m_data->processes;
}

void Preset::addProcess(std::string process)
{
    m_data->processes.push_back(process);
}

void Preset::addDomain(config::OutboundType outboundType, std::string domain)
{
    addOutboundDataField(outboundType, domain, &outbound_data_t::domain);
}

void Preset::addDomainSuffix(config::OutboundType outboundType, std::string domainSuffix)
{
    addOutboundDataField(outboundType, domainSuffix, &outbound_data_t::domainSuffix);
}

void Preset::removeDomain(config::OutboundType outboundType, size_t index)
{
    removeOutboundDataField(outboundType, index, &outbound_data_t::domain);
}

void Preset::removeDomainSuffixes(config::OutboundType outboundType, size_t index)
{
    removeOutboundDataField(outboundType, index, &outbound_data_t::domainSuffix);
}

VectorStr Preset::getDomains(config::OutboundType outboundType) const
{
    return getOutboundDataField(outboundType, &outbound_data_t::domain);
}

VectorStr Preset::getDomainSuffixes(config::OutboundType outboundType) const
{
    return getOutboundDataField(outboundType, &outbound_data_t::domainSuffix);
}

void Preset::readFile()
{
    std::string jsonBuffer;
    auto ec = glz::read_file_json<glz::opts{}>(m_data, m_path.string(), jsonBuffer);
    if (ec) {
        throw std::logic_error(glz::format_error(ec, jsonBuffer));
    }
}

void Preset::writeFile()
{
    std::string jsonBuffer;
    auto ec = glz::write_file_json<glz::opts{}>(m_data, m_path.string(), jsonBuffer);
    if (ec) {
        throw std::logic_error(glz::format_error(ec, jsonBuffer));
    }
}

void Preset::addOutboundDataField(config::OutboundType outboundType, std::string data, VectorStr outbound_data_t::* field)
{
    if (m_data->outboundData.contains(outboundType)) {
        (m_data->outboundData.at(outboundType).*field).push_back(data);
    } else {
        auto outboundData = outbound_data_t {};
        outboundData.*field = {data};
        m_data->outboundData.insert({outboundType, outboundData});
    }
}

void Preset::removeOutboundDataField(config::OutboundType outboundType, size_t index, VectorStr outbound_data_t::* field)
{
    if (m_data->outboundData.contains(outboundType)) {
        auto vectorData = (m_data->outboundData.at(outboundType).*field);
        vectorData.erase(vectorData.begin() + index);

        if (m_data->outboundData.at(outboundType).empty()) {
            m_data->outboundData.erase(outboundType);
        }
    }
}

VectorStr Preset::getOutboundDataField(config::OutboundType outboundType, VectorStr outbound_data_t::* field) const
{
    if (m_data->outboundData.contains(outboundType))
        return m_data->outboundData.at(outboundType).*field;
    return {};
}

}
