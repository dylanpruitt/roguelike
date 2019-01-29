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

    if (damage < 0) { damage = 0; }

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

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

    if (damage < 0) { damage = 0; }

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

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

    if (damage < 0) { damage = 0; }

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

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

    if (damage < 0) { damage = 0; }

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

    }

    std::cout << "The attack dealt " << damage << " damage! " << user.name << " healed " << (damage / 2) << "HP!" << std::endl;

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

        if (damage < 0) { damage = 0; }

        std::cout << "The attack dealt " << damage << " damage! " << std::endl;

    } else {
        std::cout << "Nothing happened!" << std::endl;
    }

}

void skillFunctions::arrow (Entity &user, Entity &target) {

    std::cout << user.name << " used Arrow on " << target.name << "!" << std::endl;

    const int CHANCE = 70; int random = utilityFunctions::random (1, 100);

    if (random < CHANCE) {
        int damage = user.attack + 2 - target.guard;

        target.health -= damage;

        if (damage < 0) { damage = 0; }

        std::cout << "The attack dealt " << damage << " damage! " << std::endl;
    } else {
        std::cout << "But it missed!" << std::endl;

    }

}

void skillFunctions::shield_swipe (Entity &user, Entity &target) {

    std::cout << user.name << " used Shield Swipe on " << target.name << "!" << std::endl;

    int damage = user.attack + 3 - target.guard;

    if (damage >= 0) {

        target.guard = 0;
        target.health -= damage;

    } else {

        target.guard -= damage;

    }

    user.guard += 3;

    if (damage < 0) { damage = 0; }

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

    }

    std::cout << "The attack dealt " << damage << " damage!" << std::endl;

}

void skillFunctions::triple_attack (Entity &user, Entity &target) {

    std::cout << user.name << " used Triple Attack on " << target.name << "!" << std::endl;

    for (int i = 0; i < 3; i++) {
        int damage = user.attack + 2 - target.guard;

        if (damage >= 0) {

            target.guard = 0;
            target.health -= damage;

        } else {

            target.guard -= damage;

        }

        if (damage < 0) { damage = 0; }

        if (utilityFunctions::hasPower (target, "Thorns")) {
            user.health--;

        }

        std::cout << "The attack dealt " << damage << " damage!" << std::endl;

    }

}


void skillFunctions::guard_break (Entity &user, Entity &target) {

    std::cout << user.name << " used Guard Break on " << target.name << "!" << std::endl;

    int damage = target.guard + 1;

    target.health -= damage;

    if (utilityFunctions::hasPower (target, "Thorns")) {
        user.health--;

    }

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
