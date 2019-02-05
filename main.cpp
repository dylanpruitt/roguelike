#include <iostream>
#include "Game.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"

int main()
{
    Entity player; Game game;

    std::cout << "Enter a seed (number): ";
    int seed = 0; seed = utilityFunctions::getIntegerInput ();
    game.generateMap (seed);

    std::cout << "Name your player: ";
    std::cin >> player.name;
    game.displayPaths ();
    game.loop (player);
    return 0;
}
