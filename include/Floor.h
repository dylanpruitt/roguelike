#ifndef FLOOR_H
#define FLOOR_H
#include "Room.h"
#include "Power.h"
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
        enum skills { doNothing = 0, attack, dagger, defend, leech, lastResort, restore, guardBreak, arrow,
                    shieldSwipe, tripleAttack, offering, explode, cleave, missiles, observe, shadowStrike, disarm,
                    smokebomb, mug };

        void generateFloorEntities (int floorNumber) {
            switch (floorNumber) {
                    case 1: {
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Slime");
                        enemyNames.push_back ("Shield Warrior");
                        enemyNames.push_back ("Vampire");
                        enemyNames.push_back ("Wisp");
                        skillIndices.push_back (skills::attack);
                        skillIndices.push_back (skills::defend);
                        skillIndices.push_back (skills::leech);
                        skillIndices.push_back (skills::disarm);

                    } break;
                    case 2: {
                        enemyNames.push_back ("Artifact");
                        enemyNames.push_back ("Thornbush");
                        enemyNames.push_back ("Thief");
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Crusader");
                        enemyNames.push_back ("Brute");
                        skillIndices.push_back (skills::dagger);
                        skillIndices.push_back (skills::arrow);
                        skillIndices.push_back (skills::leech);
                        skillIndices.push_back (skills::lastResort);
                        skillIndices.push_back (skills::offering);
                        skillIndices.push_back (skills::disarm);
                        skillIndices.push_back (skills::observe);
                        skillIndices.push_back (skills::smokebomb);

                    } break;
                    case 3: {
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Blue Slime");
                        enemyNames.push_back ("Minotaur");
                        enemyNames.push_back ("Crusader");
                        enemyNames.push_back ("Thief");
                        skillIndices.push_back (skills::shieldSwipe);
                        skillIndices.push_back (skills::restore);
                        skillIndices.push_back (skills::dagger);
                        skillIndices.push_back (skills::disarm);
                        skillIndices.push_back (skills::observe);
                        skillIndices.push_back (skills::smokebomb);

                    } break;
                    case 4: {
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Brute");
                        enemyNames.push_back ("Blue Slime");
                        enemyNames.push_back ("Minotaur");
                        skillIndices.push_back (skills::tripleAttack);
                        skillIndices.push_back (skills::cleave);
                        skillIndices.push_back (skills::explode);
                        skillIndices.push_back (skills::shadowStrike);
                        skillIndices.push_back (skills::smokebomb);
                    } break;
                    case 5: {
                        enemyNames.push_back ("Rock");
                        enemyNames.push_back ("Shadow");
                        enemyNames.push_back ("Beholder");
                        skillIndices.push_back (skills::attack);

                    } break;
                    case 6: {
                        enemyNames.push_back ("Rock");
                        skillIndices.push_back (skills::attack);

                    } break;
                    case 7: {
                        enemyNames.push_back ("Rock");
                        skillIndices.push_back (skills::attack);

                    } break;
                    case 8: {
                        enemyNames.push_back ("Rock");
                        skillIndices.push_back (skills::attack);

                    } break;
                    case 9: {
                        enemyNames.push_back ("Rock");
                        skillIndices.push_back (skills::attack);

                    } break;
                    case 10: {
                        enemyNames.push_back ("Rock");
                        skillIndices.push_back (skills::attack);

                    } break;
                }
        }

};

#endif // FLOOR_H
