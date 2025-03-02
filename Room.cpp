#include "Room.h"
using namespace std;

#include <string>
#include <vector>
#include <iostream>

Room::Room(std::string building, std::string number) {
    building_ = building; 
    number_ = number;
}

string Room::getBuilding() const {
    return building_;
}
string Room::getNumber() const {
    return number_;
}


void Room::addEvent(double startTime, double endTime, std::string day) {
    if (day == "Monday") {
        Monday.push_back({startTime, endTime});
    } else if (day == "Tuesday") {
        Tuesday.push_back({startTime, endTime});
    } else if (day == "Wednesday") {
        Wednesday.push_back({startTime, endTime});
    } else if (day == "Thursday") {
        Thursday.push_back({startTime, endTime});
    } else if (day == "Friday") {
        Friday.push_back({startTime, endTime});
    }
}
bool Room::isFree(double startTime, double endTime, std::string day) {
    if (day == "Monday") {
        for (const auto& block : Monday) {
            if (startTime > block[0] && startTime < block[1]) {
                return false;
            } 
            if (endTime > block[0] && endTime < block[1]) {
                return false;
            } 
        }
    } else if (day == "Tuesday") {
        for (const auto& block : Monday) {
            if (startTime > block[0] && startTime < block[1]) {
                return false;
            } 
            if (endTime > block[0] && endTime < block[1]) {
                return false;
            } 
        }
    } else if (day == "Wednesday") {
       for (const auto& block : Monday) {
            if (startTime > block[0] && startTime < block[1]) {
                return false;
            } 
            if (endTime > block[0] && endTime < block[1]) {
                return false;
            } 
        }
    } else if (day == "Thursday") {
        for (const auto& block : Monday) {
            if (startTime > block[0] && startTime < block[1]) {
                return false;
            } 
            if (endTime > block[0] && endTime < block[1]) {
                return false;
            } 
        }
    } else if (day == "Friday") {
       for (const auto& block : Monday) {
            if (startTime > block[0] && startTime < block[1]) {
                return false;
            } 
            if (endTime > block[0] && endTime < block[1]) {
                return false;
            } 
        }
    }
    return true;    
}

