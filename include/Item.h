#ifndef ITEM_H
#define ITEM_H

#include <GameObject.h>


class Item : public GameObject
{
    public:
        Item();
        virtual ~Item();
        std::string Getwriting() {return writing; }
        void Setwriting(std::string val) {writing = val; }
        std::string Getprint() {return print; }
        void Setprint(std::string val) {print = val; }
        std::string Getaction() {return action; }
        void Setaction(std::string val) {action = val; }
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
        std::string print;
        std::string action;
        bool has_turnon;
        bool turned_on;
};

#endif // ITEM_H
