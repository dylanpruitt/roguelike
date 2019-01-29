#include <iostream>
#include "Game.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"

int main()
{
    Entity player; Game game; game.initializeSkills (); game.initializePowers ();

    player.skillset [0] = &game.gameSkills [2]; player.skillset [1] = &game.gameSkills[3]; player.skillset [2] = &game.gameSkills[0];

    std::cout << "Enter a seed (number): ";
    int seed = 0; seed = utilityFunctions::getIntegerInput ();
    game.generateFloor (seed);
    std::cout << "Name your player: ";
    std::cin >> player.name;
    game.displayPaths ();
    game.loop (player);
    return 0;
}
