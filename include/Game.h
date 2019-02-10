#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Floor.h"
#include "Power.h"

class Game
{
    public:
        Game() { initializePowers (); initializeSkills (); };
        virtual ~Game();

        void battle (Entity &player, Entity &enemy);

        void displayPlayerInformation (Entity &player, Entity &enemy);

        void initializeSkills ();

        void initializePowers ();

        Entity returnEntityFromName (std::string name);

        void replaceSkill (Entity &player, Skill *rewardSkill);

        void generateMap (int seed);

        void displayRoomChoices (int roomIndex);

        void loop (Entity &player);

        void displayPaths ();

        void rewardPower (Entity &player);

        std::vector <Skill> gameSkills;

        std::vector <Power> gamePowers;

    private:
        Floor dungeon [5];

        void executeRoomLogic (Entity &player, int roomIndex);

        void shop (Entity &player, int roomIndex);

        void choosePlayerStart (Entity &player);

        Room generateRoom (Floor &parent);

        Floor generateFloor (int seed, int floorNumber);

        void displayCombatantPowers (Entity &player, Entity &enemy);

        int floor = 1;
};

#endif // GAME_H
