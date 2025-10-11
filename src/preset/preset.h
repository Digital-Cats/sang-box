#pragma once

#include <string>
#include <filesystem>

#include <glaze/glaze.hpp>

#include "preset_structures.h"

namespace preset {

class Preset
{

public:
    explicit Preset(std::string name, std::filesystem::path configFolder);
    explicit Preset(std::filesystem::path path);
    ~Preset() = default;

    VectorStr getProcesses() const;
    void addProcess(std::string process);

    void addDomain(config::OutboundType outboundType, std::string domain);
    void addDomainSuffix(config::OutboundType outboundType, std::string domainSuffix);

    void removeDomain(config::OutboundType outboundType, size_t index);
    void removeDomainSuffixes(config::OutboundType outboundType, size_t index);

    VectorStr getDomains(config::OutboundType outboundType) const;
    VectorStr getDomainSuffixes(config::OutboundType outboundType) const;

private:
    void readFile();
    void writeFile();

    void addOutboundDataField(config::OutboundType outboundType, std::string data, VectorStr outbound_data_t::* field);
    void removeOutboundDataField(config::OutboundType outboundType, size_t index, VectorStr outbound_data_t::* field);
    VectorStr getOutboundDataField(config::OutboundType outboundType, VectorStr outbound_data_t::* field) const;

private:
    PresetDataUPtr m_data;
    std::filesystem::path m_path;
};

}
