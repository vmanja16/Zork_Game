#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <list>
#include "Room.h"
#include <algorithm>
class GameManager
{
    public:
        std::list<Room> rooms; //!< Member variable "rooms"
        Room * current_room;
        std::list<std::string> commands;
        std::list<std::string> dirs;
        /** Default constructor */
        GameManager(std::list<Room> room_list);
        /** Default destructor */
        virtual ~GameManager();
        std::list<Room> Getrooms() { return rooms; }
        void Setrooms(std::list<Room> val) { rooms = val; }
        void print_rooms();
        void enterRoom(std::string room_name);
        void start();
        Room * getRoom(std::string room_name);
        std::string getCommand();
        bool checkCommandValid(std::string cmd);
        void parseCommand(std::string cmd);
        void loopGame();
        void goDirection(std::string dir);

    protected:
    private:

};

#endif // GAMEMANAGER_H
