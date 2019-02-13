#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <string>
#include <fstream>
#include <vector>

namespace PlayerStats
{

    extern int totalDamageDealt;
    extern int damageThisRun;
    extern int runVictories;

    extern std::vector <std::string> enemiesThatKilledPlayer;

    void loadStatsFromFile (std::string filename);

    void saveStatsToFile (std::string filename);

    void readFileInputUntilDelimiter (std::ifstream &file, std::string &input, std::string delimiter);

};

#endif // PLAYERSTATS_H
