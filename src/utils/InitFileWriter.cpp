#include "utils/InitFileWriter.hpp"

#include <fstream>


InitFileWriter::InitFileWriter(int scaleFactor, int chefsNumber, int waitersNumber, 
                               int twoChairsTablesNumber, int fourChairsTablesNumber,
                               int timeToEndSimulationInMinutes) {
    configValues["scaleFactor"] = scaleFactor;
    configValues["chefsNumber"] = chefsNumber;
    configValues["waitersNumber"] = waitersNumber;
    configValues["twoChairsTablesNumber"] = twoChairsTablesNumber;
    configValues["fourChairsTablesNumber"] = fourChairsTablesNumber;
    configValues["timeToEndSimulationInMinutes"] = timeToEndSimulationInMinutes;
    createConfigFile();
}

bool InitFileWriter::createConfigFile() {
    std::ofstream file(filePath);
    if(file.is_open()) {
        file << "[RestaurantSimulator]\n";
        file << "scaleFactor=" << configValues["scaleFactor"] << "\n";
        file << "chefsNumber=" << configValues["chefsNumber"] << "\n";
        file << "waitersNumber=" << configValues["waitersNumber"] << "\n";
        file << "twoChairsTablesNumber=" << configValues["twoChairsTablesNumber"] << "\n";
        file << "fourChairsTablesNumber=" << configValues["fourChairsTablesNumber"] << "\n";
        file << "timeToEndSimulationInMinutes=" << configValues["timeToEndSimulationInMinutes"] << "\n";
        file.close();
        return true;
    }
    return false;
}