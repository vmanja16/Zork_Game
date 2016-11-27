#include "Item.h"
#include <list>

Item::Item()
{
    is_item = true;
    Setturned_on(false);
    Sethas_turnon(false);
    owner = NULL;
    turnon_actions = std::list<std::string>();
    turnon_prints = std::list<std::string>();
}

Item::~Item()
{
    //dtor
}
