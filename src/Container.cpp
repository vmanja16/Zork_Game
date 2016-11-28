#include "Container.h"

Container::Container()
{
    std::list<std::string> acceptable_items = std::list<std::string>();
    std::list<std::string> items = std::list<std::string>();
    owner = NULL;
    open = false;
}

Container::~Container()
{
    //dtor
}
