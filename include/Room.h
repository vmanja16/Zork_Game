#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"
class Room: public GameObject
{
    public:
        Room();
        bool exit;
        std::map<std::string, std::string> border_map;
        virtual ~Room();
    protected:
    private:
};

#endif // ROOM_H
