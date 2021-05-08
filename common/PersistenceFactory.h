#ifndef PERSISTENCEFACTORY_H
#define PERSISTENCEFACTORY_H

#include "memory"
#include "Config.h"

class PersistenceFactory
{
public:
    PersistenceFactory() = delete;
    void operator=(const PersistenceFactory &) = delete;

    static Config& getInstance();
};

#endif // PERSISTENCEFACTORY_H
