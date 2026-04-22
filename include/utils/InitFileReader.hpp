#pragma once

#include <string>
#include <unordered_map>


class InitFileReader {
private:
    const std::string filePath = "restaurantSimulator.ini";
    std::unordered_map<std::string, int> configValues;

    bool loadConfigValues();
    std::string trim(const std::string str);
    int stringToInt(const std::string str);
    bool createDefaultConfigFile();
public:
    InitFileReader();
    std::unordered_map<std::string, int> getConfigValues() {
        return configValues;
    }
};