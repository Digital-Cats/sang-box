#pragma once

#include <memory>
#include <vector>
#include <map>

#include <tools/config_structures.h>

namespace preset {

struct preset_data_t;
struct outbound_data_t;

using VectorStr = std::vector<std::string>;
using PresetDataUPtr = std::unique_ptr<preset_data_t>;

struct preset_data_t {
    std::string name;
    VectorStr processes;

    std::map<config::OutboundType, outbound_data_t> outboundData;
};

struct outbound_data_t {
    VectorStr domain;
    VectorStr domainSuffix;

    bool empty() const {
        return domain.empty() && domainSuffix.empty();
    }
};

}

// Structures registration for JSON lib

template <>
struct glz::meta<preset::preset_data_t> {
    using T = preset::preset_data_t;
    static constexpr auto value = object(
        &T::name,
        &T::processes,
        &T::outboundData
    );
};

template <>
struct glz::meta<preset::outbound_data_t> {
    using T = preset::outbound_data_t;
    static constexpr auto value = object(
        &T::domain,
        &T::domainSuffix
    );
};
