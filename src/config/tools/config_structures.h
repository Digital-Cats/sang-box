#pragma once

#include <glaze/glaze.hpp>

#include <memory>

namespace config {

struct clash_api_t {
    std::string external_controller;
    std::map<glz::sv, glz::raw_json> extra;
};

struct experimental_t {
    std::unique_ptr<clash_api_t> clash_api = nullptr;
    std::map<glz::sv, glz::raw_json> extra;
};

struct root_config_t
{
    std::unique_ptr<experimental_t> experimental = nullptr;
    std::map<glz::sv, glz::raw_json> extra;
};

}



template <>
struct glz::meta<config::clash_api_t> {
    using T = config::clash_api_t;
    static constexpr auto value = object(
        &T::external_controller
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};

template <>
struct glz::meta<config::experimental_t> {
    using T = config::experimental_t;
    static constexpr auto value = object(
        &T::clash_api
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};

template <>
struct glz::meta<config::root_config_t> {
    using T = config::root_config_t;
    static constexpr auto value = object(
        &T::experimental
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};
