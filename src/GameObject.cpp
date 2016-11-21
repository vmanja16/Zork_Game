#include "GameObject.h"

GameObject::GameObject()
{
    is_room = false;
    is_item = false;
    is_container = false;
    is_creature = false;
}

GameObject::~GameObject()
{
    //dtor
}
