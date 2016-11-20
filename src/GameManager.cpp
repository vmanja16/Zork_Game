#include "GameManager.h"

GameManager::GameManager(std::list<Room> room_list){
    GameManager::Setrooms(room_list);
}

GameManager::~GameManager(){
    //dtor
}

Room * GameManager::getRoom(std::string room_name){
    Room * room = NULL;
    for (std::list<Room>::iterator it=rooms.begin();it != rooms.end(); it++){
        if(!room_name.compare(it->name)){
            room = &*it;
        }
    }
    return room;
}

void GameManager::print_rooms(){
    // PRINT OUT THE ROOM's CONTENTS!
    for (std::list<Room>::iterator it=rooms.begin();it != rooms.end(); it++){
        if (!it->name.empty()){
            std::cout << "Name:: " << it->name << std::endl;
        }
        if (!it->description.empty()){
            std::cout << "\tDescription:: " << it->description << std::endl;
        }
        std::cout << "\tBorders::" << std::endl;
        std::cout << "\t\tn:: " << it->border_map["n"] << std::endl;
        std::cout << "\t\ts:: " << it->border_map["s"] << std::endl;
        std::cout << "\t\te:: " << it->border_map["e"] << std::endl;
        std::cout << "\t\tw:: " << it->border_map["w"] << std::endl;
    }
}
