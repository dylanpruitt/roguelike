#ifndef EVENT_H
#define EVENT_H
#include "Skill.h"

class Event
{
    public:
        Event() {}
        virtual ~Event() {}

        std::string name;
        std::string description;
        void (*trigger)(Entity &player);

    protected:

    private:
};

#endif // EVENT_H
