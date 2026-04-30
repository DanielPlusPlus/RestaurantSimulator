#include "utils/StatsFileWriter.hpp"

#include <fstream>
#include <ctime>
#include <cstring>


StatsFileWriter::StatsFileWriter(int waitersNumber, 
                                 int chefsNumber, 
                                 int twoChairsTablesNumber, 
                                 int fourChairsTablesNumber, 
                                 int simulatonTimeInMinutes, 
                                 int totalCustomersNumberCounter, 
                                 int resigningCustomersNumberCounter, 
                                 int insideCustomersNumberCounter, 
                                 int leavingCustomersNumberCounter, 
                                 int orderedDishesNumberCounter, 
                                 int preparedDishesNumberCounter, 
                                 int servedDishesNumberCounter, 
                                 int eatenDishesNumberCounter, 
                                 int droppedDishesNumberCounter) {
    statsValues["waitersNumber"] = waitersNumber;
    statsValues["chefsNumber"] = chefsNumber;
    statsValues["twoChairsTablesNumber"] = twoChairsTablesNumber;
    statsValues["fourChairsTablesNumber"] = fourChairsTablesNumber;
    statsValues["simulationTimeInMinutes"] = simulatonTimeInMinutes;
    statsValues["totalCustomersNumber"] = totalCustomersNumberCounter;
    statsValues["resigningCustomersNumber"] = resigningCustomersNumberCounter;
    statsValues["insideCustomersNumber"] = insideCustomersNumberCounter;
    statsValues["leavingCustomersNumber"] = leavingCustomersNumberCounter;
    statsValues["orderedDishesNumber"] = orderedDishesNumberCounter;
    statsValues["preparedDishesNumber"] = preparedDishesNumberCounter;
    statsValues["servedDishesNumber"] = servedDishesNumberCounter;
    statsValues["eatenDishesNumber"] = eatenDishesNumberCounter;
    statsValues["droppedDishesNumber"] = droppedDishesNumberCounter;
}

bool StatsFileWriter::writeStatsToFile() {
    std::ofstream file(filePath, std::ios::app);
    std::time_t now = std::time(nullptr);
    char* date = std::ctime(&now);
    date[strlen(date) - 1] = '\0';
    if(file.is_open()) {
        file << "[Restaurant Simulator Stats from " << date << "]\n";
        file << "Waiters: " << statsValues["waitersNumber"] << "\n";
        file << "Chefs: " << statsValues["chefsNumber"] << "\n";
        file << "Two chairs tables: " << statsValues["twoChairsTablesNumber"] << "\n";
        file << "Four chairs tables: " << statsValues["fourChairsTablesNumber"] << "\n";
        file << "Simulation time (minutes): " << statsValues["simulationTimeInMinutes"] << "\n";
        file << "Total customers: " << statsValues["totalCustomersNumber"] << "\n";
        file << "Resigning customers: " << statsValues["resigningCustomersNumber"] << "\n";
        file << "Inside customers: " << statsValues["insideCustomersNumber"] << "\n";
        file << "Leaving customers: " << statsValues["leavingCustomersNumber"] << "\n";
        file << "Ordered dishes: " << statsValues["orderedDishesNumber"] << "\n";
        file << "Prepared dishes: " << statsValues["preparedDishesNumber"] << "\n";
        file << "Served dishes: " << statsValues["servedDishesNumber"] << "\n";
        file << "Eaten dishes: " << statsValues["eatenDishesNumber"] << "\n";
        file << "Dropped dishes: " << statsValues["droppedDishesNumber"] << "\n";
        file.close();
        return true;
    }
    return false;
}