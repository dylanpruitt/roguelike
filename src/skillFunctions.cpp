#include "SkillFunctions.h"
#include <iostream>
#include "statusFunctions.h"
#include "utilityFunctions.h"

void skillFunctions::do_nothing (Entity &user, Entity &target) {
    std::cout << user.name << " did nothing!" << std::endl;

}

void skillFunctions::dagger (Entity &user, Entity &target) {

    std::cout << user.name << " used Dagger on " << target.name << "!" << std::endl;

    int damage = user.attack + 5 - target.guard;

    if (damage >= 0) {

        target.guard = 0;
        target.health -= damage;

    } else {

        target.guard -= damage;

    }

    std::cout << "The attack dealt " << damage << " damage!" << std::endl;

}

void skillFunctions::attack (Entity &user, Entity &target) {

    std::cout << user.name << " used Attack on " << target.name << "!" << std::endl;

    int damage = user.attack + 2 - target.guard;

    if (damage >= 0) {

        target.guard = 0;
        target.health -= damage;

    } else {

        target.guard -= damage;

    }

    std::cout << "The attack dealt " << damage << " damage!" << std::endl;

}

void skillFunctions::lucky_strike (Entity &user, Entity &target) {

    std::cout << user.name << " used Lucky Strike on " << target.name << "!" << std::endl;

    int damage = user.attack + utilityFunctions::random (1, 6) - target.guard;

    if (damage >= 0) {

        target.guard = 0;
        target.health -= damage;

    } else {

        target.guard -= damage;

    }

    std::cout << "The attack dealt " << damage << " damage!" << std::endl;

}

void skillFunctions::leech (Entity &user, Entity &target) {

    std::cout << user.name << " used Leech on " << target.name << "!" << std::endl;

    int damage = user.attack + 3 - target.guard;

    if (damage >= 0) {

        target.guard = 0;
        target.health -= damage;
        user.health += (damage / 2);
        if (user.health > user.maxHealth) { user.health = user.maxHealth; }
    } else {

        target.guard -= damage;

    }

    std::cout << "The attack dealt " << damage << " damage! " << user.name << " healed " << (damage / 2) << "HP!" << std::endl;

}

void skillFunctions::poison (Entity &user, Entity &target) {
    std::cout << user.name << "  used Poison!" << std::endl;

    Status poison; poison.update = statusFunctions::poison; poison.turnsLeft = 2;

    target.statuses.push_back (&poison);
}

void skillFunctions::last_resort (Entity &user, Entity &target) {

    std::cout << user.name << " used Last Resort on " << target.name << "!" << std::endl;

    if (user.health == 1) {
        int damage = user.attack + 50 - target.guard;

        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;
        } else {

            target.guard -= damage;

        }

        std::cout << "The attack dealt " << damage << " damage! " << std::endl;

    } else {
        std::cout << "Nothing happened!" << std::endl;
    }

}

void skillFunctions::guard_break (Entity &user, Entity &target) {

    std::cout << user.name << " used Guard Break on " << target.name << "!" << std::endl;

    int damage = target.guard + 1;

    target.health -= damage;

    std::cout << "The attack dealt " << damage << " damage! " << std::endl;
}

void skillFunctions::defend (Entity &user, Entity &target) {
    std::cout << user.name << " used Defend!" << std::endl;

    user.guard += 5;

}

void skillFunctions::restore (Entity &user, Entity &target) {
    std::cout << user.name << " used Restore!" << std::endl;

    user.health += user.maxHealth / 4; if (user.health > user.maxHealth) { user.health = user.maxHealth; }

}
