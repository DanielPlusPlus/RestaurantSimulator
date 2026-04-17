#include "interiors/TablesManager.hpp"


TablesManager::TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    twoChairsTablesNumber = (twoChairsTablesNumber > 8) ? 8 : twoChairsTablesNumber;
    fourChairsTablesNumber = (fourChairsTablesNumber > 3) ? 3 : fourChairsTablesNumber;
    setUpTables(scaleFactor, twoChairsTablesNumber, fourChairsTablesNumber);
}

void TablesManager::setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    int tableNumber = 0;
    for(int i = 0; i < twoChairsTablesNumber; i++) {
        tableNumber++;
        TwoChairsTable* newTable = new TwoChairsTable(scaleFactor, 
                                                      twoChairstablesTexturesPaths[i % (sizeof(twoChairstablesTexturesPaths) / 
                                                      sizeof(std::string))], 
                                                      twoChairsTablesPositions[i], tableNumber);
        twoChairsTables.push_back(newTable);
    }
    for(int i = 0; i < fourChairsTablesNumber; i++) {
        tableNumber++;
        FourChairsTable* newTable = new FourChairsTable(scaleFactor, 
                                                        fourChairstablesTexturesPaths[i % (sizeof(fourChairstablesTexturesPaths) / 
                                                        sizeof(std::string))], 
                                                        fourChairsTablesPositions[i], tableNumber);
        fourChairsTables.push_back(newTable);
    }
}

void TablesManager::removeTable() {
    if(!twoChairsTables.empty()) {
        delete twoChairsTables.back();
        twoChairsTables.pop_back();
    }
    else if(!fourChairsTables.empty()) {
        delete fourChairsTables.back();
        fourChairsTables.pop_back();
    }
}

bool TablesManager::isFreeTable() {
    for(TwoChairsTable* table : twoChairsTables) {
        if(!table->getOccupiedStatus()){
            return true;
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(!table->getOccupiedStatus()) {
            return true;
        }
    }
    return false;
}

int TablesManager::getFreeTableNumber() {
    for(TwoChairsTable* table : twoChairsTables) {
        if(!table->getOccupiedStatus()){
            return table->getTableNumber();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(!table->getOccupiedStatus()) {
            return table->getTableNumber();
        }
    }
    return -1;
}

bool TablesManager::isFreeChair(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return !table->getOccupiedStatus();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return !table->getOccupiedStatus();
        }
    }
    return false;
}

ChairPositionsAndDirections TablesManager::getFreeChairPositions(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->occupyChairAndGetPositionsAndDirections();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->occupyChairAndGetPositionsAndDirections();
        }
    }
    return ChairPositionsAndDirections{Positions{-1.0f, -1.0f}, Positions{-1.0f, -1.0f}, 
                                       Directions::RIGHT, Directions::DOWN};
}

void TablesManager::freeChair(int tableNumber, 
                              Directions chairHorizontalDirection, 
                              Directions chairVerticalDirection) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->resetChairOccupancy(chairHorizontalDirection, 
                                       chairVerticalDirection);
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->resetChairOccupancy(chairHorizontalDirection, 
                                       chairVerticalDirection);
        }
    }
}

void TablesManager::render(sf::RenderWindow* window) {
    for(TwoChairsTable* table : twoChairsTables) {
        table->render(window);
    }
    for(FourChairsTable* table : fourChairsTables) {
        table->render(window);
    }
}
