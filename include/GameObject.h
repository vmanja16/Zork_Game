#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        void Setname(std::string val){name = val;}
        std::string Getname(){return name;}

        void Setstatus(std::string val){status = val;}
        std::string Getstatus(){return status;}

        void Setdescription(std::string val){description = val;}
        std::string Getdescription(){return description;}

        std::string name;
        std::string description;
        std::string status;
        bool is_room, is_item, is_container, is_creature;
    protected:
    private:

};

#endif // GAMEOBJECT_H
