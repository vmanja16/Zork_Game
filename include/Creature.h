#ifndef CREATURE_H
#define CREATURE_H

#include <GameObject.h>
#include <list>
#include "Room.h"
#include "Item.h"
#include "Trigger.h"

class Creature : public GameObject
{
    public:
        Creature();
        virtual ~Creature();
        Trigger condition;
        std::list<std::string> Getvulnerabilities() { return vulnerabilities; }
        void Setvulnerabilities(std::string val) { vulnerabilities.push_back(val); }
        bool Gethas_attack_condition() { return has_attack_condition; }
        void Sethas_attack_condition(bool val) { has_attack_condition = val; }
        std::list<std::string> Getattack_actions() { return attack_actions; }
        void Setattack_actions(std::string val) { attack_actions.push_back(val); }
        std::list<std::string> Getattack_prints() { return attack_prints; }
        void Setattack_prints(std::string val) { attack_prints.push_back(val); }
        Room * Getowner(){return owner;}
        void Setowner(Room * val){owner = val;}
        bool has_attack;
        void Setcondition(Trigger val){condition = val;}
        Trigger Getcondition(){return condition;}

    protected:
    private:
        std::list<std::string> vulnerabilities;
        bool has_attack_condition;
        std::list<std::string> attack_actions;
        std::list<std::string> attack_prints;
        Room * owner;
};

#endif // CREATURE_H
