#include "SkillFunctions.h"
#include <iostream>
#include "utilityFunctions.h"
#include "PlayerStats.h"
#include "Power.h"

void skillFunctions::do_nothing (Entity &user, Entity &target) {
    std::cout << user.name << " did nothing!" << std::endl;

}

void skillFunctions::dagger (Entity &user, Entity &target) {

    std::cout << user.name << " used Dagger on " << target.name << "!" << std::endl;

    basicAttack(user, target, 5);

}

void skillFunctions::attack (Entity &user, Entity &target) {

    std::cout << user.name << " used Attack on " << target.name << "!" << std::endl;

    basicAttack(user, target, 3);

}

void skillFunctions::lucky_strike (Entity &user, Entity &target) {

    std::cout << user.name << " used Lucky Strike on " << target.name << "!" << std::endl;

    basicAttack (user, target, utilityFunctions::random (1, 6));
}

void skillFunctions::leech (Entity &user, Entity &target) {

    std::cout << user.name << " used Leech on " << target.name << "!" << std::endl;

    int damage = user.attack + 3 - target.guard;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            user.health += (damage / 2);
            if (user.health > user.maxHealth) { user.health = user.maxHealth; }
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        } else {

            target.guard -= damage;

        }

        if (damage < 0) { damage = 0; }

        for (unsigned int i = 0; i < target.powers.size (); i++) {
            target.powers [i]->whenAttacked (target, user);
        }

        std::cout << "The attack dealt " << damage << " damage! " << user.name << " healed " << (damage / 2) << "HP!" << std::endl;
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }
}

void skillFunctions::last_resort (Entity &user, Entity &target) {

    std::cout << user.name << " used Last Resort on " << target.name << "!" << std::endl;
    int damage = 0;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        if (user.health == 1) {
            damage = user.attack + 50 - target.guard;

            if (damage >= 0) {

                target.guard = 0;
                target.health -= damage;
                if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

            } else {

                target.guard -= damage;

            }

            if (damage < 0) { damage = 0; }

            std::cout << "The attack dealt " << damage << " damage! " << std::endl;

        } else {
            std::cout << "Nothing happened!" << std::endl;
        }
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }


}

void skillFunctions::arrow (Entity &user, Entity &target) {

    std::cout << user.name << " used Arrow on " << target.name << "!" << std::endl;

    const int CHANCE = 70; int random = utilityFunctions::random (1, 100);
    int damage = 0;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        if (random < CHANCE) {
            damage = user.attack + 2 - target.guard;

            if (damage >= 0) {

                target.guard = 0;
                target.health -= damage;
                if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

            } else {

                target.guard -= damage;

            }

            if (damage < 0) { damage = 0; }

            std::cout << "The attack dealt " << damage << " damage! " << std::endl;
        } else {
            std::cout << "But it missed!" << std::endl;

        }
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }

}

void skillFunctions::shield_swipe (Entity &user, Entity &target) {

    std::cout << user.name << " used Shield Swipe on " << target.name << "!" << std::endl;

    int damage = user.attack + 3 - target.guard;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        } else {

            target.guard -= damage;

        }

        user.guard += 3;

        if (damage < 0) { damage = 0; }

        for (unsigned int i = 0; i < target.powers.size (); i++) {
            target.powers [i]->whenAttacked (target, user);
        }

        std::cout << "The attack dealt " << damage << " damage!" << std::endl;
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }

}

void skillFunctions::triple_attack (Entity &user, Entity &target) {

    std::cout << user.name << " used Triple Attack on " << target.name << "!" << std::endl;

    for (int i = 0; i < 3; i++) {
        basicAttack (user, target, 2);

    }

}

void skillFunctions::explode (Entity &user, Entity &target) {

    std::cout << user.name << " used Explode on " << target.name << "!" << std::endl;

    int damage = 10 - target.guard;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        } else {

            target.guard -= damage;

        }

        if (damage < 0) { damage = 0; } else { target.health -= damage; user.health -= (damage / 3); }

        std::cout << "The attack dealt " << damage << " damage! " << std::endl;
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }

}

void skillFunctions::offering (Entity &user, Entity &target) {

    std::cout << user.name << " used Offering!" << std::endl;

    user.health *= (2/3);
    user.attack++;

}

void skillFunctions::desperado (Entity &user, Entity &target) {

    std::cout << user.name << " used Desperado on " << target.name << "!" << std::endl;

    basicAttack (user, target, (10 * (1 - (user.health / user.maxHealth))));

}

void skillFunctions::cleave (Entity &user, Entity &target) {

    std::cout << user.name << " used Cleave on " << target.name << "!" << std::endl;

    basicAttack (user, target, 7);

}

void skillFunctions::guard_break (Entity &user, Entity &target) {

    std::cout << user.name << " used Guard Break on " << target.name << "!" << std::endl;

    int damage = target.guard + 1;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        target.health -= damage;
        if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        for (unsigned int i = 0; i < target.powers.size (); i++) {
            target.powers [i]->whenAttacked (target, user);
        }
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }


    std::cout << "The attack dealt " << damage << " damage! " << std::endl;
}

void skillFunctions::defend (Entity &user, Entity &target) {
    std::cout << user.name << " used Defend!" << std::endl;

    user.guard += 4;

}

void skillFunctions::restore (Entity &user, Entity &target) {
    std::cout << user.name << " used Restore!" << std::endl;

    user.health += user.maxHealth / 4; if (user.health > user.maxHealth) { user.health = user.maxHealth; }

}

void skillFunctions::absorb (Entity &user, Entity &target) {

    std::cout << user.name << " used Absorb on " << target.name << "!" << std::endl;

    int damage = 2;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}
        target.health -= damage;
        if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        for (unsigned int i = 0; i < target.powers.size (); i++) {
            target.powers [i]->whenAttacked (target, user);
        }

        if (target.health <= 0) { user.maxHealth++; }

        std::cout << "The attack dealt " << damage << " damage!" << std::endl;
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }

}

void skillFunctions::missiles (Entity &user, Entity &target) {

    std::cout << user.name << " used Missiles on " << target.name << "!" << std::endl;
    const int CHANCE = 40;

    for (int i = 0; i < utilityFunctions::random (2, 5); i++) {
        if (user.focus >= target.evade) {
            int roll = utilityFunctions::random (1, 100);

            if (roll <= CHANCE) {
                int damage = user.attack + 2 - target.guard;
                if (user.focus > target.evade) { damage += 3; user.focus--;}

                if (damage >= 0) {

                    target.guard = 0;
                    target.health -= damage;
                    if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

                } else {

                    target.guard -= damage;

                }

                if (damage < 0) { damage = 0; }

                std::cout << "The attack dealt " << damage << " damage!" << std::endl;

            } else {
                std::cout << "But it missed!" << std::endl;
            }
        } else {
            std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
        }

    }

}

void skillFunctions::evade (Entity &user, Entity &target) {
    user.evade ++;
    std::cout << user.name << " used Smokebomb!" << std::endl;

}

void skillFunctions::focus (Entity &user, Entity &target) {
    user.focus ++;
    std::cout << user.name << " used Observe!" << std::endl;

}

void skillFunctions::disarm (Entity &user, Entity &target) {
    std::cout << user.name << " used Disarm on " << target.name << "!" << std::endl;

    if (user.focus >= target.evade) {

        int damage = user.attack + 3 - target.guard;
        if (user.focus > target.evade) { damage += 3; user.focus--;}

        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        } else {

            target.guard -= damage;

        }

        target.focus--;

        if (damage < 0) { damage = 0; }

        std::cout << "The attack dealt " << damage << " damage!" << std::endl;

    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }
}

void skillFunctions::shadow_strike (Entity &user, Entity &target) {
    std::cout << user.name << " used Shadow Strike on " << target.name << "!" << std::endl;

    if (user.focus >= target.evade) {

        int damage = user.attack + 3*user.evade - target.guard;
        if (user.focus > target.evade) { damage += 3; user.focus--;}

        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }

        } else {

            target.guard -= damage;

        }

        target.focus--; user.evade = 0;

        if (damage < 0) { damage = 0; }

        std::cout << "The attack dealt " << damage << " damage!" << std::endl;

    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }
}

void skillFunctions::mug (Entity &user, Entity &target) {
    std::cout << user.name << " used Mug!" << std::endl;
    basicAttack (user, target, 3);

    int goldRobbed = utilityFunctions::random (1, 16);

    if (target.gold < goldRobbed) { goldRobbed = target.gold; }

    std::cout << user.name << " stole " << goldRobbed << " gold!" << std::endl;
    target.gold -= goldRobbed; user.gold += goldRobbed;
}

void skillFunctions::split_pain (Entity &user, Entity &target) {
    std::cout << user.name << " used Split Pain!" << std::endl;

    double userHealthPercentage = (user.health / user.maxHealth), targetHealthPercentage = (target.health / target.maxHealth);

    double splitPercentage = (userHealthPercentage + targetHealthPercentage) / 2;

    int newUserHealth = splitPercentage * user.maxHealth, newTargetHealth = splitPercentage * target.maxHealth;

    if (user.isPlayer) { PlayerStats::damageThisRun += (target.health - newTargetHealth); }
    user.health = newUserHealth; target.health = newTargetHealth;
}

void skillFunctions::wail (Entity &user, Entity &target) {
    std::cout << user.name << " used Wail! " << target.name << "'s guard fell!" << std::endl;

    target.guard -= 3;
}

void skillFunctions::basicAttack (Entity &user, Entity &target, int baseDamage) {

    int damage = user.attack + baseDamage - target.guard;

    if (user.focus >= target.evade) {
        if (user.focus > target.evade) { damage += 3; user.focus--;}

        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
            if (user.isPlayer) { PlayerStats::damageThisRun += damage; }
        } else {

            target.guard -= damage;

        }

        if (damage < 0) { damage = 0; }

        for (unsigned int i = 0; i < target.powers.size (); i++) {
            target.powers [i]->whenAttacked (target, user);
        }
        std::cout << "The attack dealt " << damage << " damage!" << std::endl;
    } else {
        std::cout << "The attack missed!" << std::endl; if (target.evade > 0) { target.evade--; }
    }

}
