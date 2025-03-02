#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>  // Include JSON library
using json = nlohmann::json;
#include <string>
#include <vector>
#include <unordered_map>

class Building;
class Room;

bool callPythonScriptAndProcessJSON(const std::string& inputURL, std::unordered_map<std::string, Building*>& buildingList);
//void readJsonFile(const json& jsonData, std::unordered_map<std::string, Building*> *BuildingList);

void processEach(const json& classObject, Room* rm);
double timeToDouble(const std::string& timeStr);
std::vector<std::string> daysOfWeekToString(const std::string& daysStr);

void readJsonFile(const std::string& filename, std::unordered_map<std::string, Building*> *BuildingList);
bool callPythonScriptWithInput( const std::string& inputString);



#endif 