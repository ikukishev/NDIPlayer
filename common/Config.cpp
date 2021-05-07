#include "Config.h"
#include "iostream"

std::string Config::getP_ndi_address() const
{
    return m_ndiAddress;
}

void Config::setP_ndi_address(const std::string &value)
{
    m_ndiAddress = m_setterWrapper(m_ndiAddressName, value);
}

std::string Config::getP_ndi_name() const
{
    return m_ndiName;
}

void Config::setP_ndi_name(const std::string &value)
{
    m_ndiName = m_setterWrapper(m_lastNdiNameName, value);
}

sf::Vector2i Config::getLastWindowPosition() const
{
    return m_lastWindowPosition;
}

void Config::setLastWindowPosition(const sf::Vector2i &lastWindowPosition)
{
    m_lastWindowPosition.x = std::stoi(m_setterWrapper(m_lastWindowPositionXName, std::to_string(lastWindowPosition.x)));
    m_lastWindowPosition.y = std::stoi(m_setterWrapper(m_lastWindowPositionYName, std::to_string(lastWindowPosition.y)));
}

Config::Config(const std::function<const std::string &(const std::string &, const std::string &)> &setterWrapper)
    : m_setterWrapper(setterWrapper),
      m_lastNdiNameName("NDIThread.LastNDIThreadName"),
      m_ndiAddressName("NDIThread.LastNDIThreadURL"),
      m_lastWindowPositionXName("Window.LastWindowPositionX"),
      m_lastWindowPositionYName("Window.LastWindowPositionY")
{

}

Config &Config::parseFromPtree(boost::property_tree::ptree ptree)
{
    this->m_ndiAddress = ptree.get<std::string>(m_ndiAddressName);
    this->m_ndiName = ptree.get<std::string>(m_lastNdiNameName);

    this->m_lastWindowPosition.x = ptree.get<int>(m_lastWindowPositionXName, 0);
    this->m_lastWindowPosition.y = ptree.get<int>(m_lastWindowPositionYName, 0);

    return *this;

}
