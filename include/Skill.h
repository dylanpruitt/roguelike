#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Entity.h"

class Skill
{
    public:
        Skill() {};
        virtual ~Skill() {};

        std::string name;
        std::string description;
        void (*use)(Entity &user, Entity &target);

    protected:

    private:
};

#endif // SKILL_H
