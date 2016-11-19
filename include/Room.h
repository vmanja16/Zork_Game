#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
#include <map>
class Room
{
    public:
        Room();
        std::map<std::string, std::string> border_map;
        Room * n, *s, *e, *w;
        std::string name, description;
        virtual ~Room();
    protected:
    private:
};

#endif // ROOM_H
