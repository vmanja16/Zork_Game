#include "Room.h"
#include <map>
#include <string>

Room::Room()
{
    n = NULL;
    s = NULL;
    e = NULL;
    w = NULL;
    //name;
    //description;
    border_map["s"] = "";
    border_map["s"] = "";
    border_map["w"] = "";
    border_map["e"] = "";
}

Room::~Room()
{
    //dtor
}
