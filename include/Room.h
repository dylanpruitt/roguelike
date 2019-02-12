#ifndef ROOM_H
#define ROOM_H
#include "Skill.h"
#include <vector>

class Room
{
    public:
        Room() {}
        virtual ~Room() {}

        /** Room types: enemy, shop, skillreward, goldreward, event, start **/
        std::string roomType = "enemy";

        Entity entityInRoom;

        std::vector <Skill> skillRewards;

        int goldReward;

        int priceOfSkills [3] = {0, 0, 0};
        int priceOfHeal = 0;

};

#endif // ROOM_H
