#ifndef SKILLFUNCTIONS_H
#define SKILLFUNCTIONS_H
#include "Entity.h"
#include "Status.h"

namespace skillFunctions
{

    void do_nothing (Entity &user, Entity &target);

    /** ATTACKS **/

    void dagger (Entity &user, Entity &target);

    void attack (Entity &user, Entity &target);

    void lucky_strike (Entity &user, Entity &target);

    void leech (Entity &user, Entity &target);

    void poison (Entity &user, Entity &target);

    void last_resort (Entity &user, Entity &target);

    void guard_break (Entity &user, Entity &target);

    /** BUFFS **/

    void defend (Entity &user, Entity &target);

    void restore (Entity &user, Entity &target);

    /** FOR USE IN FUNCTIONS BUT NOT ACTUAL SKILLS **/
    void applyStatus (Entity &target, Status status);
};


#endif // SKILLFUNCTIONS_H
