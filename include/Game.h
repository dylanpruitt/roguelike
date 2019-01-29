#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Room.h"
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

        void generateFloor (int seed);

        void displayRoomChoices (int roomIndex);

        void loop (Entity &player);

        void displayPaths ();

        std::vector <Skill> gameSkills;

        std::vector <Power> gamePowers;

    private:
        Room floorMap [27];

        void executeRoomLogic (Entity &player, int roomIndex);

        void shop (Entity &player, int roomIndex);

        Room generateRoom ();
};

#endif // GAME_H
