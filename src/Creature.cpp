#include "Creature.h"

Creature::Creature()
{
    //ctor
}

Creature::~Creature()
{
    owner = NULL;
    attack_actions = std::list<std::string>();
    attack_prints = std::list<std::string>();
    vulnerabilities = std::list<std::string>();
    has_attack = false;
}
