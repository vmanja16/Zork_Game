#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include "Trigger.h"
#include <list>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        void Settriggers(Trigger val){triggers.push_back(val);}
        std::list<Trigger> Gettriggers(){return triggers;};

        void Setname(std::string val){name = val;}
        std::string Getname(){return name;}

        void Setstatus(std::string val){status = val;}
        std::string Getstatus(){return status;}

        void Setdescription(std::string val){description = val;}
        std::string Getdescription(){return description;}

        std::list<Trigger> triggers;
        std::string name;
        std::string description;
        std::string status;
        bool is_room, is_item, is_container, is_creature;
    protected:
    private:

};

#endif // GAMEOBJECT_H
