#include "GameManager.h"

GameManager::GameManager(std::list<Room> room_list){
    GameManager::Setrooms(room_list);
    current_room = NULL;
    dirs.push_back("n");dirs.push_back("e");dirs.push_back("s");dirs.push_back("w");
    commands.insert(commands.end(), dirs.begin(), dirs.end());
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

void GameManager::enterRoom(std::string room_name){
    current_room = getRoom(room_name);
    if(!current_room->description.empty()){
        std::cout << current_room->description << std::endl;
    }
    // check triggers/items and whatnot
}

bool GameManager::checkCommandValid(std::string cmd){
    return (std::find(commands.begin(), commands.end(), cmd) != commands.end());
}

std::string GameManager::getCommand(){
    std::string cmd;
    std::cout << ">";
    std::getline(std::cin, cmd);
    if (checkCommandValid(cmd)){return cmd;}
    else{
        std::cout << "Error" << std::endl;
        return getCommand();}
}

void GameManager::parseCommand(std::string cmd){
    if (std::find(dirs.begin(), dirs.end(), cmd) != dirs.end()){
        goDirection(cmd);
    }
    // open and other commands
}

void GameManager::goDirection(std::string dir){
    std::string room_name = current_room->border_map[dir];
    if (!room_name.empty()){enterRoom(room_name);}
    else{std::cout << "Can't go there!" << std::endl;}
}

void GameManager::start(){
    enterRoom("Entrance");
    loopGame();
}

void GameManager::loopGame(){
    std::string cmd;
    while(current_room->exit == false){
        cmd = getCommand();
        parseCommand(cmd);
    }
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
