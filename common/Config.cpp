#include "Config.h"

std::string Config::getLastNdiAddress() const
{
    return m_lastNdiAddress;
}

void Config::setLastNdiAddress(const std::string &value)
{
    m_lastNdiAddress = m_setterWrapper(m_lastNdiAddressName, value);
}

std::string Config::getLastNdiName() const
{
    return m_lastNdiName;
}

void Config::setLastNdiName(const std::string &value)
{
    m_lastNdiName = m_setterWrapper(m_lastNdiNameName, value);
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
      m_lastNdiAddressName("NDIThread.LastNDIThreadURL"),
      m_lastWindowPositionXName("Window.LastWindowPositionX"),
      m_lastWindowPositionYName("Window.LastWindowPositionY")
{

}

Config &Config::parseFromPtree(boost::property_tree::ptree ptree)
{
    this->m_lastNdiAddress = ptree.get<std::string>(m_lastNdiAddressName);
    this->m_lastNdiName = ptree.get<std::string>(m_lastNdiNameName);

    this->m_lastWindowPosition.x = ptree.get<int>(m_lastWindowPositionXName, 0);
    this->m_lastWindowPosition.y = ptree.get<int>(m_lastWindowPositionYName, 0);

    return *this;

}
