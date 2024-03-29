#ifndef CONTAINER_H
#define CONTAINER_H

#include <list>
#include <GameObject.h>
#include "Room.h"

class Container : public GameObject
{
    public:
        bool isOpen(){return open;}
        void Setopen(bool val){open = val;}
        Container();
        virtual ~Container();
        std::list<std::string> Getacceptable_items() { return acceptable_items; }
        void Setacceptable_items(std::string val) { acceptable_items.push_back(val); }
        void Setitem_list(std::string val) { item_list.push_back(val); }
        Room * Getowner(){return owner;}
        void Setowner(Room * val){owner = val;}

        bool can_open;
        std::list<std::string> acceptable_items;
        std::list<std::string> item_list;
    protected:
    private:
        bool open;
        Room * owner;
};

#endif // CONTAINER_H
