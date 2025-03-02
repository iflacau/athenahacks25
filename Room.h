#ifndef ROOM_H 
#define ROOM_H 

#include <string>
#include <vector>

class Room {
    public: 
    Room(std::string building, std::string number); 

    std::string getBuilding() const;
    std::string getNumber() const; 
    
    void addEvent(double startTime, double endTime, std::string day);
    bool isFree(double startTime, double endTime, std::string day);
    
    private:
        std::string building_; 
        std::string number_; 


        std::vector<std::vector<double>> Monday;
        std::vector<std::vector<double>> Tuesday;
        std::vector<std::vector<double>> Wednesday;
        std::vector<std::vector<double>> Thursday;
        std::vector<std::vector<double>> Friday;
};

#endif