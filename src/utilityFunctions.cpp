#include "utilityFunctions.h"
#include "Power.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <limits>

int utilityFunctions::random (int min, int max) {

    int randomNumber = rand () % (max - min + 1) + min;

    return randomNumber;
}

int utilityFunctions::getIntegerInput () {

    int input = 0;

    std::cin >> input;

    while (!std::cin) {

        std::cout << "Bad value!";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> input;

    }

    return input;

}


bool utilityFunctions::hasPower (Entity &entity, std::string name) {
    for (unsigned int i = 0; i < entity.powers.size (); i++) {
        if (entity.powers [i]->name == name) {
            return true;
        }

    }

    return false;
}

