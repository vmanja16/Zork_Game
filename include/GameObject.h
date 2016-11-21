#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        std::string Getname() { return name; }
        void Setname(std::string val) { name = val; }
        std::string Getdescription() { return description; }
        void Setdescription(std::string val) { description = val; }
        std::string Getstatus() { return status; }
        void Setstatus(std::string val) { status = val; }
        std::string name;
        std::string description;
        std::string status;
    protected:
    private:

};

#endif // GAMEOBJECT_H
