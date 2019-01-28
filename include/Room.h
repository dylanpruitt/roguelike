#ifndef ROOM_H
#define ROOM_H
#include "Skill.h"

class Room
{
    public:
        Room() {}
        virtual ~Room() {}

        /** Room types: enemy, shop, skillreward, goldreward, start **/
        std::string roomType = "enemy";

        Entity entityInRoom;

        Skill skillReward;

        int goldReward;

        int priceOfSkill = 0;
        int priceOfHeal = 0;

};

#endif // ROOM_H
