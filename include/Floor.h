#ifndef FLOOR_H
#define FLOOR_H
#include "Room.h"
#include "Power.h"
#include "gameData.h"
#include <vector>

class Floor
{
    public:
        Floor () {}
        Floor (int floorNumber) { generateFloorEntities (floorNumber); }
        virtual ~Floor() {}

        Room floorMap [27];

        Power powerReward;

        std::vector <std::string> enemyNames;
        std::vector <int> skillIndices;
    protected:

    private:

        void generateFloorEntities (int floorNumber) {
            switch (floorNumber) {
                    case 1: {
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Slime");
                        enemyNames.push_back ("Shield Warrior");
                        enemyNames.push_back ("Vampire");
                        enemyNames.push_back ("Wisp");
                        skillIndices.push_back (gameData::skills::attack);
                        skillIndices.push_back (gameData::skills::defend);
                        skillIndices.push_back (gameData::skills::leech);
                        skillIndices.push_back (gameData::skills::disarm);

                    } break;
                    case 2: {
                        enemyNames.push_back ("Artifact");
                        enemyNames.push_back ("Thornbush");
                        enemyNames.push_back ("Thief");
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Crusader");
                        enemyNames.push_back ("Brute");
                        skillIndices.push_back (gameData::skills::dagger);
                        skillIndices.push_back (gameData::skills::arrow);
                        skillIndices.push_back (gameData::skills::leech);
                        skillIndices.push_back (gameData::skills::lastResort);
                        skillIndices.push_back (gameData::skills::offering);
                        skillIndices.push_back (gameData::skills::disarm);
                        skillIndices.push_back (gameData::skills::observe);
                        skillIndices.push_back (gameData::skills::smokebomb);

                    } break;
                    case 3: {
                        enemyNames.push_back ("Blue Slime");
                        enemyNames.push_back ("Minotaur");
                        enemyNames.push_back ("Crusader");
                        enemyNames.push_back ("Thief");
                        skillIndices.push_back (gameData::skills::shieldSwipe);
                        skillIndices.push_back (gameData::skills::restore);
                        skillIndices.push_back (gameData::skills::dagger);
                        skillIndices.push_back (gameData::skills::disarm);
                        skillIndices.push_back (gameData::skills::observe);
                        skillIndices.push_back (gameData::skills::smokebomb);

                    } break;
                    case 4: {
                        enemyNames.push_back ("Brute");
                        enemyNames.push_back ("Blue Slime");
                        enemyNames.push_back ("Minotaur");
                        skillIndices.push_back (gameData::skills::tripleAttack);
                        skillIndices.push_back (gameData::skills::cleave);
                        skillIndices.push_back (gameData::skills::explode);
                        skillIndices.push_back (gameData::skills::shadowStrike);
                        skillIndices.push_back (gameData::skills::smokebomb);
                    } break;
                    case 5: {
                        enemyNames.push_back ("Shadow");
                        enemyNames.push_back ("Beholder");
                        enemyNames.push_back ("Tormented Spirit");
                        skillIndices.push_back (gameData::skills::attack);

                    } break;
                }
        }

};

#endif // FLOOR_H
