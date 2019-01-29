#ifndef FLOOR_H
#define FLOOR_H
#include "Room.h"
#include "Power.h"

class Floor
{
    public:
        Floor() {}
        virtual ~Floor() {}

        Room floorMap [27];

        Power powerReward;
    protected:

    private:

};

#endif // FLOOR_H
