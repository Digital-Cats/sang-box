#include "config_obj.h"

#include <QDebug>

#include <glaze/glaze.hpp>

namespace config {

ConfigObj::ConfigObj()
    : QObject()
    , m_rootConfig()
{}

void ConfigObj::readFile(std::string jsonPath)
{
    m_jsonPath = jsonPath;
    std::string buffer;
    auto ec = glz::read_file_json<glz::opts{.error_on_unknown_keys = false}>(m_rootConfig, m_jsonPath, buffer);
    if (ec) {
        qDebug() << glz::format_error(ec, buffer);
        emit errorOccured(QString::fromStdString(glz::format_error(ec, buffer)));
    }
}

void ConfigObj::readFile(QString jsonPath)
{
    readFile(jsonPath.toStdString());
}

void ConfigObj::addClashApi()
{
    if (m_rootConfig.experimental == nullptr) {
        m_rootConfig.experimental = std::make_unique<experimental_t>();
    }
    if (m_rootConfig.experimental->clash_api == nullptr) {
        m_rootConfig.experimental->clash_api = std::make_unique<clash_api_t>();
    }

    /*
     * TODO: Introduce port logic:
     * 1) check port, which is in a config, it should be free
     * 2) if no port or current port is busy, find a new one and set it
     */
    m_rootConfig.experimental->clash_api->external_controller = "127.0.0.1:10814";
    writeDataToFile();
}

void ConfigObj::writeDataToFile()
{
    std::string buffer;
    auto ec = glz::write_file_json(m_rootConfig, m_jsonPath, buffer);
    if (ec) {
        qDebug() << glz::format_error(ec, buffer);
        emit errorOccured(QString::fromStdString(glz::format_error(ec, buffer)));
    }
}

}
