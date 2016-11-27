#ifndef ITEM_H
#define ITEM_H

#include <GameObject.h>
#include <list>


class Item : public GameObject
{
    public:
        Item();
        virtual ~Item();
        std::string Getwriting() {return writing; }
        void Setwriting(std::string val) {writing = val; }

        std::list<std::string> Getturnon_prints() {return turnon_prints; }
        void Setturnon_print(std::string val) {turnon_prints.push_back(val); }
        std::list<std::string> Getturnon_actions() {return turnon_actions; }
        void Setturnon_action(std::string val) {turnon_actions.push_back(val); }

        bool Gethas_turnon() {return has_turnon; }
        void Sethas_turnon(bool val) {has_turnon = val; }
        bool Getturned_on() {return turned_on; }
        void Setturned_on(bool val) {turned_on = val; }
        void Setowner(GameObject * val){owner = val;}
        GameObject * Getowner(){return owner;}
    protected:
    private:
        GameObject * owner;
        std::string writing;
        std::list<std::string> turnon_prints;
        std::list <std::string> turnon_actions;
        bool has_turnon;
        bool turned_on;
};

#endif // ITEM_H
