#include <iostream>
#include <string>
#include <vector> 
#include "Room.h"
#include "Building.h"
#include "Random.h"
#include <unordered_map>

#include <fstream>
#include <nlohmann/json.hpp>  // Include JSON library
using json = nlohmann::json;
using namespace std;

int main() {
    string filename = "calendar_data.json";  // Ensure this file exists
    unordered_map<string, Building*> buildingList;


   std::ifstream file("classroom_data.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    json data;
    file >> data;
    // Access data 

    string snippet1 = "https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=";
    string snippet2 = "+%7C++";
    string snippet3 = "++";

    for (const auto& item : data) { // Iterate over each *element* in the array (call it 'item')

        string room = item["room"]; // Now 'item' is an object, so you can use string keys
        replace(room.begin(), room.end(), ' ', '+');
            
        string number = item["number"];       // Assuming "age" is supposed to be an integer
        cout << "" << room << " " << number << std::endl;

        filename = "calendar_data.json";
        string url = snippet1 + room + snippet2 + number + snippet3;
        callPythonScriptWithInput(url);
        readJsonFile(filename, &buildingList);
    }

    cout << buildingList.size() << endl; 


    /*
    filename = "calendar_data.json"
    callPythonScriptWithInput("https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=BOTANY++%7C++00108++");
    readJsonFile(filename, &buildingList);
    callPythonScriptWithInput("https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=WGYOUNG+%7CCS00050++");
    readJsonFile(filename, &buildingList);
    callPythonScriptWithInput("https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=WGYOUNG+%7CCS00076++");
    readJsonFile(filename, &buildingList);
    callPythonScriptWithInput("https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=WGYOUNG+%7CCS00024++");
    readJsonFile(filename, &buildingList);

    for (const auto& bld : buildingList) {
        bld.second->getAllRooms();
    }

    

    cout << buildingList.size() << endl;

    //  cout << bld->hasAvailableRoom(8, 9, "Monday") << endl;
    //  cout << bld->hasAvailableRoom(13, 14, "Wednesday") << endl;
    //   cout << bld->hasAvailableRoom(13, 14, "Monday") << endl;

    */
} 


//callPythonScriptAndProcessJSON("https://sa.ucla.edu/ro/Public/SOC/Results/ClassroomDetail?term=25W&classroom=BOTANY++%7C++00108++", buildingList);