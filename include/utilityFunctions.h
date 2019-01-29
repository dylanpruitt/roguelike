#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H
#include "Skill.h"

namespace utilityFunctions
{
    int random (int min, int max);

    int getIntegerInput ();

    bool hasPower (Entity &entity, std::string name);
};


#endif // UTILITYFUNCTIONS_H
