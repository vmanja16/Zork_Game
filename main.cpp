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

using namespace rapidxml;
//std::string file_name = "itemsample.xml";
//std::string file_name = "roomsample.xml";
std::string file_name = "sample.txt.xml";
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

void getRoomInfo(xml_node<> * lvl_node, Room * temp_room){
    std::string value, ex;
    while(lvl_node != NULL){
        value = lvl_node->name();
        if (!value.compare("name")){
            temp_room->name = lvl_node->value();
        }
        if (!value.compare("description")){
            temp_room->description = lvl_node->value();
        }
        if (!value.compare("status")){
            temp_room->status = lvl_node->value();
        }
        if (!value.compare("border")){
            setBorder(lvl_node, temp_room );
        }
        if (!value.compare("type")){
            ex = lvl_node->value();
            if(!ex.compare("exit")){
                temp_room->exit = true;
            }
        }
        if (!value.compare("item")){
            temp_room->items_list.push_back(lvl_node->value());
        }
        lvl_node = lvl_node->next_sibling();
    }
}

void getItemInfo(xml_node<> * lvl_node, Item * temp_item){
    std::string value;
    while(lvl_node != NULL){
        value = lvl_node->name();
        if (!value.compare("name")){
            temp_item->name = lvl_node->value();
        }
        if (!value.compare("description")){
            temp_item->description = lvl_node->value();
        }
        if (!value.compare("status")){
            temp_item->status = lvl_node->value();
        }
        if(!value.compare("writing")){
            temp_item->Setwriting(lvl_node->value());
        }
        if(!value.compare("turnon")){
            temp_item->Sethas_turnon(true);
            xml_node<> * temp = lvl_node->first_node();
            std::string val;
            while(temp != NULL){
                val = temp->name();
                if(!val.compare("print")){
                    temp_item->Setprint(temp->value());
                }
                if(!val.compare("action")){
                    temp_item->Setaction(temp->value());
                }
                temp = temp->next_sibling();
            }
        }
        lvl_node = lvl_node->next_sibling();
    }
}

int main()
{

    xml_document<> doc;
    xml_node<> * mapNode, *lvl_node;
    std::list<Room> rooms;
    std::list<Item> items;
    std::map<std::string,Item> item_map;

    std::string name;

    std::ifstream t(file_name.c_str());
    std::string strr((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    char  str[strr.length()];
    strcpy( str, strr.c_str());

    // Initialize DOM Tree
    doc.parse<0>(str);

    mapNode = doc.first_node()->first_node();

    Room temp_room;
    Item temp_item;

    while(mapNode != NULL){
        name = mapNode->name();
        temp_room = Room();
        temp_item = Item();
        if(!name.compare("room")){
            getRoomInfo(mapNode->first_node(), &temp_room);
            rooms.push_back(temp_room);
        }
        else if (!name.compare("item")){
            getItemInfo(mapNode->first_node(), &temp_item);
            //items.push_back(temp_item);
            item_map[temp_item.name] = temp_item;
        }
        mapNode = mapNode->next_sibling(); // move ptr
    }

    // 2nd pass through rooms to add item instances with their respective room owners
    for (std::list<Room>::iterator it=rooms.begin();it != rooms.end(); it++){
        for (std::list<std::string>::iterator itt=it->items_list.begin();itt != it->items_list.end(); itt++){
            Item item_instance = item_map[*itt]; item_instance.Setowner(&*it); items.push_back(item_instance);
        }
    }

    // START GAME
    GameManager game_manager = GameManager(rooms);
    game_manager.Setitem_instances(items);
    game_manager.Setitem_map(item_map);
    //game_manager.print_rooms();
/*
    for (std::list<Item>::iterator it=items.begin();it != items.end(); it++){
        std::cout << "Name:: " << it->name << std::endl;
        std::cout << "\tDescription:: " << it->description << std::endl;
        std::cout << "\tStatus:: " << it->description << std::endl;
        std::cout << "\tWriting::" << it->Getwriting() << std::endl;
        std::cout << "\tTurnOn::" << it->Gethas_turnon() << std::endl;
        std::cout << "\t\tPrint::" << it->Getprint() << std::endl;
        std::cout << "\t\tAction::" << it->Getaction() << std::endl;
        if(it->Getowner()!=NULL){std::cout << "\t\tOwner::" << it->Getowner()->Getname() << std::endl;}
    }
*/
    game_manager.start();


    return 0;
}

