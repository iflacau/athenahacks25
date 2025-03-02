#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>  // Include JSON library
#include "Random.h"
#include "Room.h"
#include "Building.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream> // For string streams
#include <iomanip> // For std::setprecision and std::fixed

using json = nlohmann::json;
using namespace std;

void readJsonFile(const string& filename, unordered_map<string, Building*> *BuildingList) {
    ifstream inputFile(filename);
    json jsonData;


    if (inputFile.is_open()) {
        try {
            inputFile >> jsonData;  // Read JSON file
        } catch (json::parse_error& e) {
            cerr << "JSON Parse Error: " << e.what() << endl;
        }
        inputFile.close();
    } else {
        cerr << "Error: Could not open file " << filename << endl;
    }


    string building_name = jsonData[0].value("meet_bdg", "N/A");
    Building* bld = nullptr;  // Declare bld as a local pointer here
    Room* rm = nullptr; 

    
    //see if the building has already been made, if not make it
    auto it = BuildingList->find(building_name);
    if (it != BuildingList->end()) {
        bld = it->second;
    } else {
        bld  = new Building(building_name);
        BuildingList-> operator[](building_name) = bld; // Insert into the map
    }

    string room_name = jsonData[0].value("meet_rm", "N/A");
    rm = new Room(building_name, room_name); 
    bld->addRoom(rm);
    
    for (const auto& classObject : jsonData) {
        if (classObject.is_object()) {
            processEach(classObject, rm);
        }
    }
}


bool callPythonScriptWithInput( const std::string& inputString) {
    std::string pythonInterpreter = "python3"; // Or "python"
    std::string command = pythonInterpreter + " " + "./html_parser.py";

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "w"), pclose); // Open pipe for writing

    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return false; // Indicate failure
    }

    // Send the input string to the Python script via the pipe (stdin)
    fprintf(pipe.get(), "%s\n", inputString.c_str()); // Write the string and a newline
    fflush(pipe.get()); // Ensure all data is flushed to the pipe

    int returnCode = pclose(pipe.get()); // Close the pipe and get return code
    if (returnCode == 0) {
        //std::cout << "Python script executed successfully." << std::endl;
        return true; // Indicate success
    } else {
        std::cerr << "Python script exited with error code: " << returnCode << std::endl;
        return false; // Indicate failure
    }
}
void processEach(const json& classObject, Room* rm) {
    // Access various keys from each JSON object (each "large bracket")
    string startTime = classObject.value("strt_time", "N/A");
    string endTime = classObject.value("stop_time", "N/A");
    string building = classObject.value("meet_bdg", "N/A");
    string daysOfWeek = classObject.value("Days_in_week", "N/A");

    double realStart =  timeToDouble(startTime); 
    double realEnd = timeToDouble(endTime); 
    vector <string> days = daysOfWeekToString(daysOfWeek); 

    for (string day: days) {
        rm->addEvent(realStart, realEnd, day);
    }

} 

// Function to convert "HH:MM:SS" time string to a double (HH.MM)
double timeToDouble(const std::string& timeStr) {
    double timeDouble = 0.0;
    std::stringstream ss(timeStr);
    int hours, minutes, seconds;
    char colon1, colon2;

    if (ss >> hours >> colon1 >> minutes >> colon2 >> seconds &&
        colon1 == ':' && colon2 == ':') {
        timeDouble = static_cast<double>(hours) + static_cast<double>(minutes) / 100.0;
        // To ensure max decimal is .59, we can clamp the minutes if needed, though it shouldn't be necessary
        if (minutes > 59) {
            timeDouble = static_cast<double>(hours) + 0.59; // or handle error as you see fit
        } else {
            timeDouble = static_cast<double>(hours) + static_cast<double>(minutes) / 100.0;
        }
    } else {
        // Handle parsing error, perhaps return a special value or throw an exception
        std::cerr << "Warning: Invalid time format: " << timeStr << ". Returning 0.0" << std::endl;
        return 0.0; // Or throw an exception for better error handling
    }
    return timeDouble;
}

// Function to convert Days_in_week string to full day names
vector<string> daysOfWeekToString(const string& daysStr) {
    vector<string> days;

    for (char dayChar : daysStr) {
        switch (dayChar) {
            case 'M': days.push_back("Monday"); break;
            case 'T': days.push_back("Tuesday"); break;
            case 'W': days.push_back("Wednesday"); break;
            case 'R': days.push_back("Thursday"); break;
            case 'F': days.push_back("Friday"); break;
            case 'S': days.push_back("Saturday"); break;
            case 'U': days.push_back("Sunday"); break;
            case ' ': // Ignore spaces
            default:  // Ignore any other characters (or handle as error if needed)
                break;
        }
    }
    return days;
}


/*gRAVEYARD YEAHHHH




*/