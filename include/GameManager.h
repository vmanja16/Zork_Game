#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <list>
#include "Room.h"

class GameManager
{
    public:
        std::list<Room> rooms; //!< Member variable "rooms"
        /** Default constructor */
        GameManager(std::list<Room> room_list);
        /** Default destructor */
        virtual ~GameManager();
        /** Access rooms
         * \return The current value of rooms
         */
        std::list<Room> Getrooms() { return rooms; }
        /** Set rooms
         * \param val New value to set
         */
        void Setrooms(std::list<Room> val) { rooms = val; }
        void print_rooms();
        Room * getRoom(std::string room_name);


    protected:
    private:

};

#endif // GAMEMANAGER_H
