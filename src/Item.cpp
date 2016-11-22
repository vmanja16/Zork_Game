#include "Item.h"

Item::Item()
{
    is_item = true;
    Setturned_on(false);
    Sethas_turnon(false);
    owner = NULL;
}

Item::~Item()
{
    //dtor
}
