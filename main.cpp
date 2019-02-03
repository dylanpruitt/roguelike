#include <iostream>
#include "Game.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"

int main()
{
    Entity player; Game game;

    player.skillset [0] = &game.gameSkills [2]; player.skillset [1] = &game.gameSkills[3]; player.skillset [2] = &game.gameSkills[0];
    std::cout << "Enter a seed (number): ";
    int seed = 0; seed = utilityFunctions::getIntegerInput ();
    game.generateMap (seed);

    std::cout << "Select a loadout:\n[1] Warrior\n -- Low defensive abilities but offensive-focused. Start with No Guard.\n[2] Defender\n -- A defensive-based loadout. User starts with Thorns." << std::endl;
    int choice = 0;

    while (choice < 1 || choice > 2) {
        choice = utilityFunctions::getIntegerInput ();
    }

    if (choice == 1) {
        player.skillset [0] = &game.gameSkills [7]; player.skillset [1] = &game.gameSkills[2]; player.skillset [2] = &game.gameSkills[5];
        player.powers.push_back (&game.gamePowers [1]);
        player.maxHealth = 20;
        player.health = player.maxHealth;
    } else {
        player.skillset [0] = &game.gameSkills [1]; player.skillset [1] = &game.gameSkills[3]; player.skillset [2] = &game.gameSkills[3];
        player.powers.push_back (&game.gamePowers [6]);
    }

    std::cout << "Name your player: ";
    std::cin >> player.name;
    game.displayPaths ();
    game.loop (player);
    return 0;
}
