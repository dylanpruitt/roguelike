#include "PlayerStats.h"
#include <iostream>

namespace PlayerStats {

    int damageThisRun = 0;
    int totalDamageDealt = 0;
    int runVictories = 0;

    std::vector <std::string> enemiesThatKilledPlayer;

    void loadStatsFromFile (std::string filename) {
        std::ifstream file (filename.c_str ());

        if (file.is_open())  {
            file >> totalDamageDealt;

            int enemiesSize = 0;
            file >> enemiesSize;

            for (unsigned int i = 0; i < enemiesSize; i++) {
                std::string name;
                readFileInputUntilDelimiter (file, name, "|");

                enemiesThatKilledPlayer.push_back (name);
            }
            file >> runVictories;
            file.close ();

        }
    }

    void saveStatsToFile (std::string filename) {
        std::ofstream file (filename.c_str ());

        if (file.is_open()) {
            file << totalDamageDealt << "\n";

            file << enemiesThatKilledPlayer.size () << "\n";

            for (unsigned int i = 0; i < enemiesThatKilledPlayer.size (); i++) {

                file << enemiesThatKilledPlayer [i] << " | \n";

            }
            file << runVictories << "\n";
            file.close ();

        }
    }

    void readFileInputUntilDelimiter (std::ifstream &file, std::string &input, std::string delimiter) {

        std::string line;

        input = "";

        if (file.is_open()) {

            while (line != delimiter) {

                file >> line;

                if (line != delimiter) {

                    input += line + " ";

                }

            }

            input.pop_back ();

        }

    }
};

