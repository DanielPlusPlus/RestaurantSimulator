#pragma once

#include <string>
#include <unordered_map>


class InitFileWriter {
private:
    const std::string filePath = "restaurantSimulator.ini";\
    std::unordered_map<std::string, int> configValues;
public:
    InitFileWriter(int scaleFactor, int chefsNumber, 
                   int waitersNumber, 
                   int timeToEndSimulationInMinutes);
    bool createConfigFile();
};