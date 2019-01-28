#ifndef STATUS_H
#define STATUS_H
#include "Skill.h"

class Status
{
    public:
        Status() {}
        virtual ~Status() {}

        std::string name;

        int turnsLeft;

        void (*update)(Entity &entity, int turnsLeft);

};

#endif // STATUS_H
