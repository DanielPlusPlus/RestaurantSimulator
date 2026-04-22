#include "utils/InitFileReader.hpp"

#include <fstream>


InitFileReader::InitFileReader() {
    if(!loadConfigValues()) {
        configValues["scaleFactor"] = 1;
        configValues["chefsNumber"] = 1;
        configValues["waitersNumber"] = 1;
        configValues["twoChairsTablesNumber"] = 8;
        configValues["fourChairsTablesNumber"] = 3;
        configValues["timeToEndSimulationInMinutes"] = 1;
        createDefaultConfigFile();
    }
}

bool InitFileReader::loadConfigValues() {
    std::ifstream file(filePath);
    if(file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {
            if(line.empty() || line[0] == ';') {
                continue;
            }

            size_t equalPos = line.find('=');
            if(equalPos != std::string::npos) {
                std::string key = line.substr(0, equalPos);
                std::string value = line.substr(equalPos + 1);

                key = trim(key);
                value = trim(value);

                if(key == "scaleFactor") {
                    configValues["scaleFactor"] = stringToInt(value);
                }
                else if(key == "chefsNumber") {
                    configValues["chefsNumber"] = stringToInt(value);
                }
                else if(key == "waitersNumber") {
                        configValues["waitersNumber"] = stringToInt(value);
                }
                else if(key == "twoChairsTablesNumber") {
                    configValues["twoChairsTablesNumber"] = stringToInt(value);
                }
                else if(key == "fourChairsTablesNumber") {
                    configValues["fourChairsTablesNumber"] = stringToInt(value);
                }
                else if(key == "timeToEndSimulationInMinutes") {
                    configValues["timeToEndSimulationInMinutes"] = stringToInt(value);
                }
            }
        }
        file.close();
        return true;
    }
    return false;
}

std::string InitFileReader::trim(const std::string str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == std::string::npos || last == std::string::npos) ? "" : 
            str.substr(first, (last - first + 1));
}

int InitFileReader::stringToInt(const std::string str) {
    try {
        return std::stoi(str);
    }
    catch(const std::invalid_argument& e) {
        return 1;
    }
}

bool InitFileReader::createDefaultConfigFile() {
    std::ofstream file(filePath);
    if(file.is_open()) {
        file << "[RestaurantSimulator]\n";
        file << "scaleFactor=1\n";
        file << "chefsNumber=1\n";
        file << "waitersNumber=1\n";
        file << "twoChairsTablesNumber=8\n";
        file << "fourChairsTablesNumber=3\n";
        file << "timeToEndSimulationInMinutes=1\n";
        file.close();
        return true;
    }
    return false;
}
