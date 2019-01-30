#ifndef SKILLFUNCTIONS_H
#define SKILLFUNCTIONS_H
#include "Entity.h"

namespace skillFunctions
{

    void do_nothing (Entity &user, Entity &target);

    /** ATTACKS **/

    void dagger (Entity &user, Entity &target);

    void attack (Entity &user, Entity &target);

    void lucky_strike (Entity &user, Entity &target);

    void leech (Entity &user, Entity &target);

    void last_resort (Entity &user, Entity &target);

    void guard_break (Entity &user, Entity &target);

    void arrow (Entity &user, Entity &target);

    void shield_swipe (Entity &user, Entity &target);

    void triple_attack (Entity &user, Entity &target);

    void explode (Entity &user, Entity &target);

    void desperado (Entity &user, Entity &target);

    void cleave (Entity &user, Entity &target);

    void absorb (Entity &user, Entity &target);

    /** BUFFS **/

    void defend (Entity &user, Entity &target);

    void restore (Entity &user, Entity &target);

    void offering (Entity &user, Entity &target);

};


#endif // SKILLFUNCTIONS_H
