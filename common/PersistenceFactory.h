#ifndef PERSISTENCEFACTORY_H
#define PERSISTENCEFACTORY_H

#include "memory"
#include "IPersistence.hpp"
#include "Config.h"

class PersistenceFactory
{
public:
    PersistenceFactory() = delete;
    void operator=(const PersistenceFactory &) = delete;

    static std::weak_ptr<IPersistence<Config>> getInstance();
};

#endif // PERSISTENCEFACTORY_H
