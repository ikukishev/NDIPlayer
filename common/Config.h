#ifndef CONFIG_H
#define CONFIG_H

#include <boost/property_tree/ptree.hpp>
#include "string"
#include <functional>
#include <SFML/System/Vector2.hpp>

class Config
{
private:
    std::function<const std::string&(const std::string&, const std::string&)> m_setterWrapper;

    const std::string m_lastNdiNameName;
    const std::string m_ndiAddressName;
    const std::string m_lastWindowPositionXName;
    const std::string m_lastWindowPositionYName;

    std::string m_ndiName;
    std::string m_ndiAddress;
    sf::Vector2i m_lastWindowPosition;

public:
    Config(const std::function<const std::string&(const std::string&, const std::string&)>& setterWrapper);

    Config& parseFromPtree(boost::property_tree::ptree ptree);
    std::string getP_ndi_address() const;
    void setP_ndi_address(const std::string &value);
    std::string getP_ndi_name() const;
    void setP_ndi_name(const std::string &value);
    sf::Vector2i getLastWindowPosition() const;
    void setLastWindowPosition(const sf::Vector2i &lastWindowPosition);
};

#endif // CONFIG_H
