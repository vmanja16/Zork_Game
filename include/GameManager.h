#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <list>
#include "Room.h"
#include "Item.h"
#include "Creature.h"
#include "Container.h"
#include <algorithm>
#include <map>
#include <vector>
class GameManager
{
    public:
        Room inventory;
        std::map<std::string, Item> item_map;
        std::map<std::string, Container> container_map;
        std::map<std::string, Creature> creature_map;
        std::list<Item> item_instances;
        std::list<Container> container_instances;
        std::list<Creature> creature_instances;
        void Setitem_map(std::map<std::string, Item> val){
            item_map = val;
        }
        void Setcontainer_map(std::map<std::string, Container> val){
            container_map = val;
        }
        void Setcreature_map(std::map<std::string, Creature> val){
            creature_map = val;
        }
        void Setitem_instances(std::list<Item> val){
            item_instances = val;
        }
        void Setcontainer_instances(std::list<Container> val){
            container_instances = val;
        }
        void Setcreature_instances(std::list<Creature> val){
            creature_instances = val;
        }
        void attack(std::vector<std::string> cmd_list);
        void open(std::vector<std::string> cmd_list);
        void take(std::vector<std::string> cmd_list);
        void drop(std::vector<std::string> cmd_list);
        void read(std::vector<std::string> cmd_list);
        void turnon(std::vector<std::string> cmd_list);
        void parseAction(std::string action);
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
        void print_item_instances();
        void enterRoom(std::string room_name);
        void start();
        Room * getRoom(std::string room_name);
        std::string getCommand();
        bool checkCommandValid(std::string cmd);
        void parseCommand(std::string cmd);
        void loopGame();
        void goDirection(std::string dir);
        Container * getContainerInstance(std::string container_name);
        void add(std::vector<std::string> action_split);
        void update(std::vector<std::string> action_split);

    protected:
    private:

};

#endif // GAMEMANAGER_H
