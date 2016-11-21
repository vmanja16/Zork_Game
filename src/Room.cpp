#include "Room.h"
#include <map>
#include <string>

Room::Room()
{
    border_map["s"] = "";
    border_map["s"] = "";
    border_map["w"] = "";
    border_map["e"] = "";
    exit = false;
    is_room = true;
}

Room::~Room()
{
    //dtor
}
