#include "PersistenceFactory.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "common/Constants.h"
#include <iostream>

const std::string m_lastNdiNameName = "NDIThread.LastNDIThreadName";
const std::string m_lastNdiAddressName = "NDIThread.LastNDIThreadURL";
const std::string m_lastWindowPositionXName = "Window.LastWindowPositionX";
const std::string m_lastWindowPositionYName = "Window.LastWindowPositionY";

class PersistenceIni: public Config {
private:
    boost::property_tree::ptree m_values;

    const std::string& configSetterWrapper(const std::string& key, const std::string& newValue) {
        m_values.put(key, newValue);
        boost::property_tree::write_ini(Constants::INI_PATH, m_values);
        return newValue;
    }

    void parseFromPtree(boost::property_tree::ptree ptree)
    {
        this->m_lastNdiAddress = ptree.get<std::string>(m_lastNdiAddressName);
        this->m_lastNdiName = ptree.get<std::string>(m_lastNdiNameName);

        this->m_lastWindowPosition = std::make_tuple(ptree.get<int>(m_lastWindowPositionXName, 0), ptree.get<int>(m_lastWindowPositionYName, 0));
    }
public:
    PersistenceIni()
        : Config(),  m_values()
    {
        try {
            boost::property_tree::ini_parser::read_ini(Constants::INI_PATH, m_values);
            parseFromPtree(m_values);
        }  catch (std::exception exp) {
            std::cout << exp.what() << std::endl;
        }
    }

    void setLastNdiAddress(const std::string &value)
    {
        m_lastNdiAddress = configSetterWrapper(m_lastNdiAddressName, value);
    }

    void setLastNdiName(const std::string &value)
    {
        m_lastNdiName = configSetterWrapper(m_lastNdiNameName, value);
    }

    void setLastWindowPosition(int x, int y)
    {
        this->m_lastWindowPosition = std::make_tuple(
                    std::stoi(configSetterWrapper(m_lastWindowPositionXName, std::to_string(x))),
                    std::stoi(configSetterWrapper(m_lastWindowPositionYName, std::to_string(y))));
    }
};

Config &PersistenceFactory::getInstance()
{
    static PersistenceIni sVar;

    return sVar;
}
