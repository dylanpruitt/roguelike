#ifndef EVENT_H
#define EVENT_H


class Event
{
    public:
        Event() {}
        virtual ~Event() {}

        std::string name;
        std::string description;
        void (*use)(Entity &user, Entity &target);

    protected:

    private:
};

#endif // EVENT_H
