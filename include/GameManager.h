#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <list>
#include "Room.h"
#include "Item.h"
#include <algorithm>
#include <map>
#include <vector>
class GameManager
{
    public:
        Room inventory;
        std::map<std::string, Item> item_map;
        std::list<Item> item_instances;
        void Setitem_map(std::map<std::string, Item> val){
            item_map = val;
        }
        void Setitem_instances(std::list<Item> val){
            item_instances = val;
        }
        void take(std::vector<std::string> cmd_list);
        void drop(std::vector<std::string> cmd_list);
        void read(std::vector<std::string> cmd_list);
        void printInventory();
        bool game_exit;
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
