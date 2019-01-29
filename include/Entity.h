#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <vector>

class Skill;

class Power;

class Entity
{
    public:
        Entity() {}
        virtual ~Entity() {}

        static const int NUMBER_OF_SKILLS = 3;

        std::string name = "default";

        int health = 13;
        int maxHealth = 13;

        int attack = 0;
        int guard = 0;

        int gold = 24;

        Skill *skillset [NUMBER_OF_SKILLS];

        Skill *rewardSkill;

        std::vector <Power*> powers;

        void (*ai)(Entity &user, Entity &target, int turnCounter);

    protected:

    private:
};

#endif // ENTITY_H
