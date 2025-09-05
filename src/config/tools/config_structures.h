#pragma once

#include <glaze/glaze.hpp>

#include <memory>

namespace config {

struct clash_api_t;
struct experimental_t;
struct rule_t;
struct route_t;
struct root_config_t;

using RootConfigUPtr = std::unique_ptr<root_config_t>;
using VectorStrUptr = std::unique_ptr<std::vector<std::string>>;
using VectorRulesUPtr = std::unique_ptr<std::vector<rule_t>>;



struct clash_api_t {
    std::string external_controller;
    std::map<glz::sv, glz::raw_json> extra;
};

struct experimental_t {
    std::unique_ptr<clash_api_t> clash_api = nullptr;
    std::map<glz::sv, glz::raw_json> extra;
};

struct rule_t {
    VectorStrUptr domain = nullptr;
    VectorStrUptr domain_suffix = nullptr;
    VectorStrUptr process_name = nullptr;
    std::string outbound;
    std::map<glz::sv, glz::raw_json> extra;
};

struct route_t {
    VectorRulesUPtr rules = nullptr;
    std::map<glz::sv, glz::raw_json> extra;
};

struct root_config_t
{
    std::unique_ptr<experimental_t> experimental = nullptr;
    route_t route;
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
struct glz::meta<config::rule_t> {
    using T = config::rule_t;
    static constexpr auto value = object(
        &T::domain,
        &T::domain_suffix,
        &T::process_name,
        &T::outbound
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};

template <>
struct glz::meta<config::route_t> {
    using T = config::route_t;
    static constexpr auto value = object(
        &T::rules
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};

template <>
struct glz::meta<config::root_config_t> {
    using T = config::root_config_t;
    static constexpr auto value = object(
        &T::experimental,
        &T::route
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};
