#ifndef POWER_H
#define POWER_H
#include "Entity.h"

class Power
{
    public:
        Power() {}
        virtual ~Power() {}

        std::string name;

        std::string description;

        void (*use)(Entity &user, int turnCounter);
};
#endif // POWER_H
