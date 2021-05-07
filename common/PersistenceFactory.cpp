#include "PersistenceFactory.h"
#include "iostream"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "common/Constants.h"

class PersistenceIni: public IPersistence<Config> {
private:
    boost::property_tree::ptree m_values;
    Config m_config;

    const std::string& configSetterWrapper(const std::string& key, const std::string& newValue) {
        m_values.put(key, newValue);
        boost::property_tree::write_ini(Constants::INI_PATH, m_values);
        return newValue;
    }
public:
    PersistenceIni()
        :  m_values(), m_config(std::bind(&PersistenceIni::configSetterWrapper, this, std::placeholders::_1, std::placeholders::_2))
    {}

    bool init() {
        try {
            boost::property_tree::ini_parser::read_ini(Constants::INI_PATH, m_values);
            m_config.parseFromPtree(m_values);
        }  catch (std::exception exp) {
            std::cout << exp.what() << std::endl;
            return false;
        }

        return true;
    }

    Config& get() {
        return m_config;
    }
};

std::weak_ptr<IPersistence<Config>> PersistenceFactory::getInstance()
{
    static auto sVar = [](){

        auto persistence = std::make_shared<PersistenceIni>();
        persistence->init();

        return persistence;
    }();

    return sVar;
}
