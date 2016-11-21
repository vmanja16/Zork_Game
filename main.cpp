#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <map>
#include <fstream>
#include <streambuf>
#include "rapidxml.hpp"
//#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "Room.h"
#include "GameManager.h"
#include "Item.h"

//using namespace std;
using namespace rapidxml;
std::string file_name = "roomsample.xml";
//std::string file_name = "sample.txt.xml";
void setBorder(xml_node<> * lvl_node, Room * room){
    xml_node<> * node = lvl_node->first_node(); //dir or name
    std::string name, value, dir, border_name;
    while(node != NULL){
        name = node->name(); value = node->value();
        if(!name.compare("direction")){dir = value[0];}
        if(!name.compare("name")){border_name = value;}
        node = node->next_sibling();
    }
    (room->border_map)[dir] = border_name;
}

int main()
{

    xml_document<> doc;
    xml_node<> * mapNode, *lvl_node;
    std::list<Room> rooms;
    Room temp_room;
    std::string name, value, ex;

    std::ifstream t(file_name.c_str());
    std::string strr((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    char  str[strr.length()];
    strcpy( str, strr.c_str());

    // Initialize DOM Tree
    doc.parse<0>(str);

    mapNode = doc.first_node()->first_node();

// get Rooms

    while(mapNode != NULL){
        name = mapNode->name();
        if(!name.compare("room")){
            temp_room = Room();
            lvl_node = mapNode->first_node();

            while(lvl_node != NULL){
                value = lvl_node->name();
                if (!value.compare("name")){
                    temp_room.name = lvl_node->value();
                }
                if (!value.compare("description")){
                    temp_room.description = lvl_node->value();
                }
                if (!value.compare("border")){
                    setBorder(lvl_node, &temp_room );
                }
                if (!value.compare("status")){
                    temp_room.status = lvl_node->value();
                }
                if (!value.compare("type")){
                    ex = lvl_node->value();
                    if(!ex.compare("exit")){
                        temp_room.exit = true;
                    }
                }
                lvl_node = lvl_node->next_sibling();
            }
            rooms.push_back(temp_room);
        }
        mapNode = mapNode->next_sibling(); // move ptr
    }

    GameManager game_manager = GameManager(rooms);
    //game_manager.print_rooms();
    game_manager.start();

// TODO: 2nd pass to actually add instances of items/containers


    return 0;
}
