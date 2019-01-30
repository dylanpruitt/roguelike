#ifndef POWERFUNCTIONS_H
#define POWERFUNCTIONS_H
#include "Skill.h"

namespace powerFunctions
{

    void spike (Entity &user, int turnCounter);

    void grow_strength (Entity &user, int turnCounter);

    void no_guard (Entity &user, int turnCounter);

    void regenerate (Entity &user, int turnCounter);

    void wither (Entity &user, int turnCounter);

    void metal_body (Entity &user, int turnCounter);

    void strength_boost (Entity &user, int turnCounter);

    void ethereal_hourglass (Entity &user, int turnCounter);

};

#endif // POWERFUNCTIONS_H
