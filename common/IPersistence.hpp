#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include "string"
#include "memory"
#include "iostream"

template<class T>
class IPersistence {

protected:
    IPersistence()
    {}

public:

    IPersistence(IPersistence &other) = delete;
    void operator=(const IPersistence &) = delete;

    virtual T& get() = 0;

    virtual ~IPersistence() {}
};

#endif // IPERSISTENCE_H
