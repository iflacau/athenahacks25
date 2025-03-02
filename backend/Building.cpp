#include "Building.h"
#include "Room.h"
#include <iostream>
using namespace std;

Building:: Building(std::string name){
    name_ = name;
}

Building::~Building() {
        for (Room* room : allRooms) {
            delete room; // Delete each Room object
        }
        allRooms.clear(); // Clear the vector of pointers
    }

bool Building::hasAvailableRoom(double startTime, double endTime, std::string day) {
    vector<Room*> availableRooms = getAvailableRooms(startTime, endTime, day);
    if (availableRooms.size() == 0) {
        return false;
    } else {
        return true;
    }
}

std::vector<Room*> Building::getAllRooms() {
    for (Room* rm: allRooms) {
        std::cout << rm -> getBuilding() << rm -> getNumber() << std::endl;
    }
    return allRooms;
}

std::vector<Room*> Building::getAvailableRooms(double startTime, double endTime, std::string day) {
   vector<Room*> availableRooms;
   for (Room* rm: allRooms) {
        if(rm->isFree(startTime, endTime, day)) {
            availableRooms.push_back(rm);
        }
    }
    return availableRooms;
}



std::string Building::getName() const {
    return name_;
}
void Building::addRoom(Room* newRoom) {
    allRooms.push_back(newRoom);
}