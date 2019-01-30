#include "powerFunctions.h"
#include <iostream>

void powerFunctions::spike (Entity &user, int turnCounter) {
    int FIRST_TURN = 1;
    if (turnCounter == FIRST_TURN) {
        std::cout << user.name << " becomes surrounded by spikes!" << std::endl;
    }
}

void powerFunctions::grow_strength (Entity &user, int turnCounter) {
    if (turnCounter % 2 == 0) {
        user.attack++;
        std::cout << user.name << "'s strength grew!" << std::endl;
    }
}

void powerFunctions::no_guard (Entity &user, int turnCounter) {
    if (turnCounter == 1) { user.attack += 3; }

    user.guard = -3;
}

void powerFunctions::regenerate (Entity &user, int turnCounter) {
    if (turnCounter % 2 == 1) {
        user.health += 2;
    }

    if (user.health > user.maxHealth) {
        user.health = user.maxHealth;

    }

}

void powerFunctions::wither (Entity &user, int turnCounter) {
    user.health -= 2;

    user.guard = -1 * turnCounter + 1;

}

void powerFunctions::metal_body (Entity &user, int turnCounter) {
    user.guard += 2;

}

void powerFunctions::strength_boost (Entity &user, int turnCounter) {
    if (turnCounter == 1) { user.attack += 1; }

}

void powerFunctions::ethereal_hourglass (Entity &user, int turnCounter) {
    if (turnCounter % 5 == 0) {
        user.attack += 5; std::cout << user.name << "'s power sharply increases!" << std::endl;
    } else if (turnCounter % 5 == 1 && turnCounter > 1) {
        user.attack -= 5; std::cout << user.name << "'s power returns to normal!" << std::endl;
    }

}

void powerFunctions::lunar_energy (Entity &user, int turnCounter) {
    if (turnCounter % 6 < 3) {
        user.attack++; std::cout << user.name << "'s power is growing!" << std::endl;
    } else {
        user.attack--; std::cout << user.name << "'s power is waning!" << std::endl;
    }

}
