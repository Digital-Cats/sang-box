#pragma once

#include <glaze/glaze.hpp>

#include <memory>
#include <set>

namespace config {

// https://sing-box.sagernet.org/configuration/outbound/
enum class outbound_type_t {
    direct,
    block,
    socks,
    http,
    shadowsocks,
    vmess,
    trojan,
    wireguard,
    hysteria,
    vless,
    shadowtls,
    tuic,
    hysteria2,
    anytls,
    tor,
    ssh,
    dns,
    selector,
    urltest
};

struct clash_api_t;
struct experimental_t;
struct outbound_t;
struct rule_t;
struct route_t;
struct root_config_t;

using RootConfigUPtr = std::unique_ptr<root_config_t>;
using SetStrPtr = std::shared_ptr<std::set<std::string>>;
using StringUPtr = std::unique_ptr<std::string>;
using OutboundPtr = std::shared_ptr<outbound_t>;
using RulePtr = std::shared_ptr<rule_t>;
using VectorOutbounds = std::vector<OutboundPtr>;
using VectorRules = std::vector<RulePtr>;
using ExtraMap = std::map<glz::sv, glz::raw_json>;



struct clash_api_t {
    std::string external_controller;
    ExtraMap extra;
};

struct experimental_t {
    std::unique_ptr<clash_api_t> clash_api = nullptr;
    ExtraMap extra;
};

struct outbound_t {
    outbound_type_t type;
    std::string tag;
    ExtraMap extra;
};

struct rule_t {
    SetStrPtr domain = nullptr;
    SetStrPtr domain_suffix = nullptr;
    SetStrPtr process_name = nullptr;
    StringUPtr outbound;
    ExtraMap extra;
};

struct route_t {
    VectorRules rules;
    ExtraMap extra;
};

struct root_config_t
{
    std::unique_ptr<experimental_t> experimental = nullptr;
    route_t route;
    VectorOutbounds outbounds;
    ExtraMap extra;
};

}



template <>
struct glz::meta<config::outbound_type_t> {
    using enum config::outbound_type_t;
    static constexpr auto value = glz::enumerate(
        direct,
        block,
        socks,
        http,
        shadowsocks,
        vmess,
        trojan,
        wireguard,
        hysteria,
        vless,
        shadowtls,
        tuic,
        hysteria2,
        anytls,
        tor,
        ssh,
        dns,
        selector,
        urltest
    );
};

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
struct glz::meta<config::outbound_t> {
    using T = config::outbound_t;
    static constexpr auto value = object(
        &T::type,
        &T::tag
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
        &T::outbounds,
        &T::route,
        &T::experimental
    );

    static constexpr auto unknown_write{&T::extra};
    static constexpr auto unknown_read{&T::extra};
};
