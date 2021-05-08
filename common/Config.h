#ifndef CONFIG_H
#define CONFIG_H

#include "string"
#include <boost/core/noncopyable.hpp>
#include <tuple>

class Config: private boost::noncopyable
{
protected:
    std::string m_lastNdiName;
    std::string m_lastNdiAddress;
    std::tuple<int, int> m_lastWindowPosition;

public:
    std::string getLastNdiAddress() const;
    virtual void setLastNdiAddress(const std::string &value) = 0;
    std::string getLastNdiName() const;
    virtual void setLastNdiName(const std::string &value) = 0;
    std::tuple<int, int> getLastWindowPosition() const;
    virtual void setLastWindowPosition(int x, int y) = 0;
};

#endif // CONFIG_H
