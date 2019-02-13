#include <iostream>
#include "Game.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"
#include "PlayerStats.h"

void displayGameStatistics () {
    std::cout << "PLAYER STATS\nTotal Damage Dealt: " << PlayerStats::totalDamageDealt << "\nTotal Runs Won: " << PlayerStats::runVictories << std::endl;
    std::cout << "Killed by:" << std::endl;

    std::vector <std::string> killerNames; std::vector <int> killCount;

    for (unsigned int i = 0; i < PlayerStats::enemiesThatKilledPlayer.size (); i++) {
        bool isDuplicate = false;
        for (unsigned int j = 0; j < killerNames.size (); j++) {
            if (PlayerStats::enemiesThatKilledPlayer [i] == killerNames [j]) {
                killCount [j]++; i++; isDuplicate = true;
            }
        }
        if (!isDuplicate) { killerNames.push_back (PlayerStats::enemiesThatKilledPlayer [i]); killCount.push_back (1); }
    }

    for (unsigned int i = 0; i < killerNames.size (); i++) {
        std::cout << killerNames [i] << " (" << killCount [i] << ")" << std::endl;
    }
}

int main()
{
    Entity player; player.isPlayer = true; Game game; PlayerStats::loadStatsFromFile ("stats.save");
    char input = ' ';

    while (input != 'P' && input != 'p') {
        std::cout << "[P]lay Game | [V]iew Stats | Game [O]ptions" << std::endl;

        std::cin >> input;
        if (input == 'V' || input == 'v') {
            displayGameStatistics ();
        }
        if (input == 'O' || input == 'o') {
            std::cout << "Game Options\nSkill Lock (" << game.skillLock << ")\n --  You can't replace the same skill twice in a row.\n[1] Set True - [0] Set False" << std::endl;
            int choice = -1;
            while (choice < 0 || choice > 1) {
                choice = utilityFunctions::getIntegerInput ();
            }

            game.skillLock = (bool) choice;
        }
    }

    std::cout << "Enter a seed (number): ";
    int seed = 0; seed = utilityFunctions::getIntegerInput ();
    game.generateMap (seed);

    std::cout << "Name your player: ";
    std::cin >> player.name;
    game.displayPaths ();
    game.loop (player);

    return 0;
}
