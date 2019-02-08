#include <iostream>
#include "Game.h"
#include "skillFunctions.h"
#include "utilityFunctions.h"
#include "PlayerStats.h"

int main()
{
    Entity player; player.isPlayer = true; Game game; PlayerStats::loadStatsFromFile ("stats.save");
    char input = ' ';

    while (input != 'P' && input != 'p') {
        std::cout << "[P]lay Game or [V]iew Stats" << std::endl;

        std::cin >> input;

        if (input == 'V' || input == 'v') {
            std::cout << "PLAYER STATS\nTotal Damage Dealt: " << PlayerStats::totalDamageDealt << std::endl;
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
