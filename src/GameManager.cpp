#include "GameManager.h"
#include "string.h"
#include <vector>
#include <string>
#include <sstream>
GameManager::GameManager(std::list<Room> room_list){
    // TODO: NEED TO GET THE ITEM_INSTANCE LIST!
    GameManager::Setrooms(room_list);
    current_room = NULL;
    dirs.push_back("n");dirs.push_back("e");dirs.push_back("s");dirs.push_back("w");
    ///commands.insert(commands.end(), dirs.begin(), dirs.end());
    commands.push_back("open exit");
    commands.push_back("open"); commands.push_back("put"); commands.push_back("take");
    commands.push_back("i"); commands.push_back("drop"); commands.push_back("read");
    commands.push_back("turn"); commands.push_back("attack"); commands.push_back("put");
    game_exit = false;
    inventory = Room();
    inventory.Setname("inventory");
}
GameManager::~GameManager(){}
Room * GameManager::getRoom(std::string room_name){
    Room * room = NULL;
    for (std::list<Room>::iterator it=rooms.begin();it != rooms.end(); it++){
        if(!room_name.compare(it->name)){
            room = &*it;
        }
    }
    return room;
}
Container * GameManager::getContainerInstance(std::string container_name){
    Container * container = NULL;
    for (std::list<Container>::iterator it=container_instances.begin();it != container_instances.end(); it++){
        if(!container_name.compare(it->name)){
            container = &*it;
        }
    }
    return container;
}
void GameManager::enterRoom(std::string room_name){
    current_room = getRoom(room_name);
    if(!current_room->description.empty()){
        std::cout << current_room->description << std::endl;
    }
    // check triggers/items and whatnot
}
bool GameManager::checkCommandValid(std::string cmd){
    std::string command = cmd;
    std::vector<std::string> cmd_split;
    std::istringstream iss(cmd);
    for(std::string cmd; iss >> cmd;){cmd_split.push_back(cmd);}
    if(cmd_split.empty()){return false;}
    if(std::find(dirs.begin(), dirs.end(), command) != dirs.end()){return true;}
    return (std::find(commands.begin(), commands.end(), cmd_split[0]) != commands.end());
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
    std::string command = cmd;
    std::vector<std::string> cmd_split;
    std::istringstream iss(cmd);
    for(std::string cmd; iss >> cmd;){cmd_split.push_back(cmd);}
    std::string cmd_0 = cmd_split[0];
    // GameManager::checkTriggers(command){return if triggered};
    if (std::find(dirs.begin(), dirs.end(), command) != dirs.end()){goDirection(command);}
    else if(!cmd_0.compare("take")){take(cmd_split);}
    else if(!cmd_0.compare("drop")){drop(cmd_split);}
    else if(!cmd_0.compare("i")){printInventory();}
    else if(!cmd_0.compare("read")){read(cmd_split);}
    else if(!cmd_0.compare("turn")){turnon(cmd_split);}
    else if(!command.compare("open exit")){if(current_room->exit){game_exit = true;}else{std::cout<<"Error"<<std::endl;}}
    else if(!cmd_0.compare("open")){open(cmd_split);}
    else if(!cmd_0.compare("attack")){attack(cmd_split);}
    else if(!cmd_0.compare("put")){put(cmd_split);}
    // n,w,s,e,i,                  --> done
    //take(item),                  --> done
    //open(container),             --> done
    //open exit,                   --> done
    //read (item)                  --> done
    //drop(item),                  --> done
    //put(item) in (container)     --> done
    //turnon (item),               --> done
    //attack (creature) with (item)  X TODO: check conditions
    //update                       --> done
    //add                          --> done
    //delete                       --> done
    //GameOver                     --> done
    //Triggers                       X
}
/** ====================== PUT ==================================*/
void GameManager::put(std::vector<std::string> cmd_list){
    bool in_inventory=false, put_in = false, is_item = true;
    if(cmd_list.size() != 4){std::cout << "Error" << std::endl; return;}
    if(cmd_list[2].compare("in")){std::cout << "Error" << std::endl; return;}
    // Get container
    Container * container = getContainerInstance(cmd_list[3]);
    if(container == NULL){std::cout << "Error" << std::endl;return;}
    if(container->Getowner()->Getname().compare(current_room->Getname())){std::cout << "Error" << std::endl;return;}
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        if(!it->Getname().compare(cmd_list[1])){is_item = true; break;}
    }
    if(!is_item){std::cout << "Error" << std::endl;return;}
    // Check item in inventory and add to container if possible
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        if(!it->Getname().compare(cmd_list[1])){
            if(it->Getowner()==NULL){continue;}
            if(!it->Getowner()->Getname().compare("inventory")){
                in_inventory=true;
                // Check if item is acceptable{}
                if (container->acceptable_items.empty() && container->isOpen()){
                    it->Setowner(container); put_in = true;
                }
                if(std::find(container->acceptable_items.begin(),
                    container->acceptable_items.end(), cmd_list[1]) != container->acceptable_items.end()){
                    it->Setowner(container); put_in = true;
                    container->can_open = true;
                }
                break;
            }
        }
    }
    if (!in_inventory){std::cout << "Error: Item " << cmd_list[1] << " is not in inventory." << std::endl; return;}
    if(!put_in){std::cout << "Error" << std::endl;}
    else{std::cout << "Item " << cmd_list[1] << " added to " << cmd_list[3] << "." << std::endl;}
}
/** ====================== ATTACK =====================================================*/
void GameManager::attack(std::vector<std::string> cmd_list){
    bool in_inventory = false, in_room = false;;
    std::list<std::string> prints, actions;
    if(cmd_list.size() != 4){std::cout << "Error::" << std::endl; return;}
    if(cmd_list[2].compare("with")){std::cout << "Error:" << std::endl; return;}
    // check if item in inventory
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        if(!it->Getname().compare(cmd_list[3])){
            if(it->Getowner()==NULL){continue;}
            if(!it->Getowner()->Getname().compare("inventory")){ in_inventory=true;break;}
        }
    }
    if (!in_inventory){std::cout << "Error: Item " << cmd_list[3] << " is not in inventory." << std::endl; return;}

    for (std::list<Creature>::iterator it=creature_instances.begin(); it != creature_instances.end(); it++){
        if(!it->Getname().compare(cmd_list[1])){
            if(it->Getowner()==NULL){continue;}
            if(!it->Getowner()->Getname().compare(current_room->Getname())){
                if(!it->has_attack){break;}
                std::list<std::string> vul = it->Getvulnerabilities();
                if(std::find(vul.begin(),vul.end(), cmd_list[3]) == vul.end()){break;} // check vulnerable
                if (checkCondition(it->condition)){
                    prints = creature_map[it->Getname()].Getcondition().Gettrigger_prints();
                    actions = creature_map[it->Getname()].Getcondition().Gettrigger_actions();
                }
                else{break;}
                in_room=true; break;
            }
        }
    }
    // DO THE ACTIONS!
    if(in_room){
        std::cout << "You attack the " << cmd_list[1] << " with the " << cmd_list[3] << "." << std::endl;
        for(std::list<std::string>::iterator iter=prints.begin(); iter != prints.end(); iter++){
            std::cout << *iter << std::endl;//
        }
        for(std::list<std::string>::iterator iter=actions.begin(); iter != actions.end(); iter++){
            parseAction(*iter);
        }
    }
    else{std::cout << "Error" << std::endl;return;}

}
bool GameManager::checkCondition(Trigger trig){
     // CHECK Condition
    for(std::list<Item>::iterator it = item_instances.begin(); it != item_instances.end(); it++){
        if(!it->Getname().compare(trig.Getobject())){
            if(!trig.Getstatus().empty()){ return !it->Getstatus().compare(trig.Getstatus());}
            else if(it->Getowner()==NULL){return trig.Gethas().compare("yes");} // true if has=="no"
            else if(!trig.Gethas().compare("yes")){return !trig.Getowner_name().compare(it->Getowner()->Getname());}
            else{return trig.Getowner_name().compare(it->Getowner()->Getname());}
        }
    }
    for(std::list<Container>::iterator it = container_instances.begin(); it != container_instances.end(); it++){
        if(!it->Getname().compare(trig.Getobject())){
            if(!trig.Getstatus().empty()){ return (!it->Getstatus().compare(trig.Getstatus()));}
            else if(it->Getowner()==NULL){return trig.Gethas().compare("yes");} // true if has=="no"
            else if(!trig.Gethas().compare("yes")){return !trig.Getowner_name().compare(it->Getowner()->Getname());}
            else{return trig.Getowner_name().compare(it->Getowner()->Getname());}
        }
    }
    for(std::list<Creature>::iterator it = creature_instances.begin(); it != creature_instances.end(); it++){
        if(!it->Getname().compare(trig.Getobject())){
            if(!trig.Getstatus().empty()){ return (!it->Getstatus().compare(trig.Getstatus()));}
            else if(it->Getowner()==NULL){return trig.Gethas().compare("yes");} // true if has=="no"
            else if(!trig.Gethas().compare("yes")){return !trig.Getowner_name().compare(it->Getowner()->Getname());}
            else{return trig.Getowner_name().compare(it->Getowner()->Getname());}
        }
    }
    for(std::list<Room>::iterator it = rooms.begin(); it != rooms.end(); it++){
        if(!it->Getname().compare(trig.Getobject())){
            if(!trig.Getstatus().empty()){ return (!it->Getstatus().compare(trig.Getstatus()));}
            else{return false;}
        }
    }
    return false;
}
/**  ===================== OPEN =================================================*/
void GameManager::open(std::vector<std::string> cmd_list){
    bool opened = false,has_items = false;
    std::list<Item> container_items;
    if(cmd_list.size() <=1){std::cout << "Open what?" << std::endl; return;}
    else{
        for (std::list<Container>::iterator con=container_instances.begin();con != container_instances.end(); con++){
            if(!con->can_open){break;}
            if(!con->Getname().compare(cmd_list[1])){
                if(con->Getowner()->Getname() == current_room->Getname()){
                    // OPEN THE CONTAINER!
                    con->Setopen(true);
                    for(std::list<Item>::iterator itt=item_instances.begin(); itt != item_instances.end(); itt++){
                        if(itt->Getowner()==NULL){continue;}
                        if( !itt->Getowner()->Getname().compare(con->Getname())){
                            if (!has_items){
                                std::cout << cmd_list[1] << " contains " << itt->Getname();
                                has_items = true;
                            }
                            else{std::cout <<", " << itt->Getname();}
                        }
                    }
                    opened = true;
                }
            }
        }
        if(opened==false){std::cout << "Error" << std::endl; return;}
        if(!has_items){std::cout << cmd_list[1] << " is empty." << std::endl;}
        else{std::cout << std::endl;}
    }
}
/** ====================== READ ===========================================================================*/
void GameManager::read(std::vector<std::string> cmd_list){
    bool read = false;
    if(cmd_list.size() <=1){
        std::cout << "Read what?" << std::endl;
    }
    else{
        for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
            if(!it->Getname().compare(cmd_list[1])){
                if(it->Getowner()==NULL){continue;}
                if(!it->Getowner()->Getname().compare("inventory")){
                    if(!it->Getwriting().empty()){
                        std::cout << it->Getwriting() << std::endl;
                    }
                    else{std::cout << "Nothing written" << std::endl;}
                    read= true; break;
               }
            }
        }
        if(!read){std::cout << "Error: Item " << cmd_list[1] << " is not in inventory." << std::endl;}
    }
}
/** ====================== TURNON ========================================================================== */
void GameManager::turnon(std::vector<std::string> cmd_list){
    std::list<std::string> prints, actions;
    bool turned = false;
    if(cmd_list.size() != 3){std::cout << "Error" << std::endl; return;}
    if(cmd_list[1].compare("on")){std::cout << "Error" << std::endl;return;}
    else{
        for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
            if(!it->Getname().compare(cmd_list[2])){
                if(it->Getowner()==NULL){continue;}
                if(!it->Getowner()->Getname().compare("inventory")){
                    if (it->Gethas_turnon()){
                        prints = it->Getturnon_prints();
                        actions = it->Getturnon_actions();
                        for(std::list<std::string>::iterator iter=prints.begin(); iter != prints.end(); iter++){
                            std::cout << *iter << std::endl;//
                        }
                        for(std::list<std::string>::iterator iter=actions.begin(); iter != actions.end(); iter++){
                            parseAction(*iter);
                        }
                        turned= true; break;
                    }
                    else{turned=true; std::cout << "Error: Item " << cmd_list[2] << " cannot turn on." << std::endl; break;}
               }
            }
        }
        if(!turned){std::cout << "Error: Item " << cmd_list[1] << " is not in inventory." << std::endl;}
    }
}
/** ====================== DROP ==============================================*/
void GameManager::drop(std::vector<std::string> cmd_list){
    bool dropped = false;
    if(cmd_list.size() <=1){
        std::cout << "Drop what?" << std::endl;
    }
    else{
        for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
            if(!it->Getname().compare(cmd_list[1])){
                if(it->Getowner()==NULL){continue;}
                if(!it->Getowner()->Getname().compare("inventory")){
                    it->Setowner(current_room);
                    dropped = true; break;
               }
            }
        }
        if(dropped){std::cout << "Item " << cmd_list[1] << " dropped" << std::endl;}
        else{std::cout << "Error: Item " << cmd_list[1] << " is not in inventory." << std::endl;}
    }
}
/** ====================== TAKE =======================================*/
void GameManager::take(std::vector<std::string> cmd_list){
    bool taken = false;
    if(cmd_list.size() <=1){std::cout << "Take what?" << std::endl;}
    else{
        for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
            if(!it->Getname().compare(cmd_list[1])){
                if(it->Getowner()==NULL){continue;}
                if(!it->Getowner()->Getname().compare(current_room->Getname())){
                    it->Setowner(&inventory);
                    taken = true; break;
                }
                for(std::list<Container>::iterator con=container_instances.begin();con != container_instances.end(); con++){
                    if (con->Getowner()==NULL){continue;}
                    if(!con->isOpen()){continue;}
                    if (!con->Getowner()->Getname().compare(current_room->Getname())){
                        if(!it->Getowner()->Getname().compare(con->Getname())){
                            it->Setowner(&inventory);
                            taken = true; break;
                        }

                    }
                }
            }
        }
        if(taken){std::cout << "Item " << cmd_list[1] <<
            " added to inventory." << std::endl;
        }
        else{std::cout << "Error" << std::endl;}
    }
}
/** ====================== INVENTORY =======================================*/
void GameManager::printInventory(){
    std::cout << "Inventory: ";
    bool has_items = false;
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        if(it->Getowner()==&inventory){
            if (!has_items){
                std::cout << it->Getname();
                has_items = true;
            }
            else{
                std::cout <<", " << it->Getname();
            }
        }
    }
    if(!has_items){std::cout << "empty";}
    std::cout << std::endl;
}
/** ====================== MOVE =======================================*/
void GameManager::goDirection(std::string dir){
    std::string room_name = current_room->border_map[dir];
    if (!room_name.empty()){enterRoom(room_name);}
    else{std::cout << "Can't go that way!" << std::endl;}
}
/** ====================== ACTIONS ==============================================*/
void GameManager::parseAction(std::string action){
    std::string act = action;
    std::vector<std::string> action_split;
    std::istringstream iss(action);
    for(std::string action; iss >> action;){action_split.push_back(action);}
    std::string act0 = action_split[0];
    if (!act0.compare("Update")){update(action_split);}
    else if(!act0.compare("Add")){ add(action_split);}
    else if(!act0.compare("Delete")){Delete(action_split);} // TODO: Delete objects
    else if(!act.compare("Game Over")){game_exit=true;}
    else{parseCommand(act);}
}
void GameManager::update(std::vector<std::string> action_split){
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        if(!it->Getname().compare(action_split[1])){
             it->Setstatus(action_split[3]); // assumes we have a status in idx:3
        }
    }
    for (std::list<Room>::iterator it=rooms.begin();it != rooms.end(); it++){
        if(!it->Getname().compare(action_split[1])){
             it->Setstatus(action_split[3]); // assumes we have a status in idx:3
        }
    }
    for (std::list<Container>::iterator it=container_instances.begin();it != container_instances.end(); it++){
        if(!it->Getname().compare(action_split[1])){
             it->Setstatus(action_split[3]); // assumes we have a status in idx:3
        }
    }
    for (std::list<Creature>::iterator it=creature_instances.begin();it != creature_instances.end(); it++){
        if(!it->Getname().compare(action_split[1])){
             it->Setstatus(action_split[3]); // assumes we have a status in idx:3
        }
    }
}
void GameManager::Delete(std::vector<std::string> action_split){
    // Remove Item
    std::list<Item>::iterator it=item_instances.begin();
    while (it != item_instances.end()){
        if(!it->Getname().compare(action_split[1])){
            item_instances.erase(it++); break;
        }
        else{it++;}
    }
    // Remove Container
    std::list<Container>::iterator con=container_instances.begin();
    while(con != container_instances.end()){
        if(!con->Getname().compare(action_split[1])){
            container_instances.erase(con++); break;
        }
        else{con++;}
    }
        // Remove Creature
    std::list<Creature>::iterator cre=creature_instances.begin();
    while(cre != creature_instances.end()){
        if(!cre->Getname().compare(action_split[1])){
            creature_instances.erase(cre++); break;
        }
        else{cre++;}
    }
    // Remove Room
    std::list<Room>::iterator rm=rooms.begin();
    while (rm != rooms.end()){
        if(!rm->Getname().compare(action_split[1])){
            rooms.erase(rm++);
        }
        else{
            if(!rm->border_map["n"].compare(action_split[1])){rm->border_map["n"]="";}
            else if(!rm->border_map["s"].compare(action_split[1])){rm->border_map["s"]="";}
            else if(!rm->border_map["w"].compare(action_split[1])){rm->border_map["w"]="";}
            else if(!rm->border_map["e"].compare(action_split[1])){rm->border_map["e"]="";}
            rm++;
        }
    }

}
void GameManager::add(std::vector<std::string> action_split){
    std::string obj = action_split[1], owner_name = action_split[3];
    GameObject * owner;
    Room * room = getRoom(owner_name);
    Container * container = getContainerInstance(owner_name);
    if(room != NULL){owner = room;}else{owner=container;}
    if(container_map.find(obj) != container_map.end()){ // is container!
        Container new_container = container_map[obj];
        for (std::list<std::string>::iterator itt=new_container.item_list.begin();itt != new_container.item_list.end(); itt++){
            Item item_instance = item_map[*itt]; item_instance.Setowner(&new_container); item_instances.push_back(item_instance);
        }
        new_container.Setowner(room);
        container_instances.push_back(new_container);
    }
    else if(item_map.find(obj) != item_map.end()){ // is item
        Item new_item = item_map[obj];
        new_item.Setowner(owner);
        item_instances.push_back(new_item);
    }
    else if(creature_map.find(obj) != creature_map.end()){ // is container!
        Creature new_creature= creature_map[obj];
        new_creature.Setowner(room);
        creature_instances.push_back(new_creature);
    }

}
/** ====================== GAME CONTROL    =========================*/
void GameManager::start(){
    enterRoom("Entrance");
    loopGame();
}
void GameManager::loopGame(){
    std::string cmd;
    while(!game_exit){
        cmd = getCommand();
        parseCommand(cmd);
    }
    std::cout << "Game Over" << std::endl;
}
void GameManager::print_item_instances(){
    for (std::list<Item>::iterator it=item_instances.begin();it != item_instances.end(); it++){
        std::cout << "Name:: " << it->name << std::endl;
        std::cout << "\tDescription:: " << it->description << std::endl;
        std::cout << "\tStatus:: " << it->description << std::endl;
        std::cout << "\tWriting::" << it->Getwriting() << std::endl;
        std::cout << "\tTurnOn::" << it->Gethas_turnon() << std::endl;
        //std::cout << "\t\tPrint::" << it->Getprint() << std::endl;
        //std::cout << "\t\tAction::" << it->Getaction() << std::endl;
        if(it->Getowner()!=NULL){std::cout << "\t\tOwner::" << it->Getowner()->Getname() << std::endl;}
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
