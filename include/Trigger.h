#ifndef TRIGGER_H
#define TRIGGER_H
#include <list>
#include <string>
class Trigger
{
    public:
        Trigger();
        virtual ~Trigger();
        std::string Gethas() { return has; }
        void Sethas(std::string val) { has = val; }
        std::string Getobject() { return object; }
        void Setobject(std::string val) { object = val; }
        std::string Getowner_name() { return owner_name; }
        void Setowner_name(std::string val) { owner_name = val; }
        std::string Getcommand() { return command; }
        void Setcommand(std::string val) { command = val; }
        std::string Gettype() { return type; }
        void Settype(std::string val) { type = val; }
        std::string Getstatus() { return status; }
        void Setstatus(std::string val) { status = val; }
        std::list<std::string> Gettrigger_prints() { return trigger_prints; }
        void Settrigger_prints(std::string val) { trigger_prints.push_back(val); }
        std::list<std::string> Gettrigger_actions() { return trigger_actions; }
        void Settrigger_actions(std::string val) { trigger_actions.push_back(val); }
    protected:
    private:
        std::string has;
        std::string object;
        std::string owner_name;
        std::string command;
        std::string type;
        std::string status;
        std::list<std::string> trigger_prints;
        std::list<std::string> trigger_actions;
};

#endif // TRIGGER_H
