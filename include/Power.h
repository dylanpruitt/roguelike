#ifndef POWER_H
#define POWER_H
#include "Entity.h"
#include "powerFunctions.h"

class Power
{
    public:
        Power() {}
        virtual ~Power() {}

        std::string name;

        std::string description;

        void (*use)(Entity &user, int turnCounter);

        void (*onCombatEnd)(Entity &user, int turnCounter) = powerFunctions::do_nothing;

        void (*whenAttacked)(Entity &user, Entity &enemy) = powerFunctions::do_nothing;

        void (*whenDebuffApplied)(Entity &user, Entity &enemy) = powerFunctions::do_nothing;

        void (*onBlock)(Entity &user, Entity &enemy) = powerFunctions::do_nothing;

};
#endif // POWER_H
