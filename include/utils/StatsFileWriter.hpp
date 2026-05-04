#pragma once

#include <string>
#include <unordered_map>


class StatsFileWriter {
private:
    const std::string filePath = "stats.txt";
    std::unordered_map<std::string, int> statsValues;
public:
    StatsFileWriter(int chefsNumber, 
                    int waitersNumber, 
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
                    int droppedDishesNumberCounter);
    bool writeStatsToFile();
};