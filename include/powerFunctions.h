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

    void lunar_energy (Entity &user, int turnCounter);

    void eagle_eye (Entity &user, int turnCounter);

    void elusive_shadow (Entity &user, int turnCounter);

    void do_nothing (Entity &user, int turnCounter);

    void do_nothing (Entity &user, Entity &enemy);

    void deal_spike_damage (Entity &user, Entity &enemy);

};

#endif // POWERFUNCTIONS_H
