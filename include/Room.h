#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
#include <map>
#include <list>
#include "GameObject.h"
class Room: public GameObject
{
    public:
        Room();
        bool exit;
        std::list<std::string> items_list, containers_list;
        std::map<std::string, std::string> border_map;
        virtual ~Room();
    protected:
    private:
};

#endif // ROOM_H
