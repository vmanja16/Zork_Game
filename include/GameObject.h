#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        std::string name;
        std::string description;
        std::string status;
        bool is_room, is_item, is_container, is_creature;
    protected:
    private:

};

#endif // GAMEOBJECT_H
