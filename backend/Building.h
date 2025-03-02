#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include "Room.h"

class Building {
    public: 
        Building(std::string name);
        ~Building();
        std::string getName() const; 
        void addRoom(Room* newRoom);
        bool hasAvailableRoom(double startTime, double endTime, std::string day);
        std::vector<Room*> getAllRooms();
        std::vector<Room*> getAvailableRooms(double startTime, double endTime, std::string day);

    
    private:
        std::string name_;
        std::vector<Room*> allRooms;

};

#endif