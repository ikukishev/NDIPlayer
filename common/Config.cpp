#include "Config.h"

std::string Config::getLastNdiAddress() const
{
    return m_lastNdiAddress;
}

std::string Config::getLastNdiName() const
{
    return m_lastNdiName;
}

std::tuple<int, int> Config::getLastWindowPosition() const
{
    return m_lastWindowPosition;
}
