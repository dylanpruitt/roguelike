#include "utilityFunctions.h"
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
