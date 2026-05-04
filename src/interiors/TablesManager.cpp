#include "interiors/TablesManager.hpp"


TablesManager::TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    twoChairsTablesNumber = (twoChairsTablesNumber > 8) ? 8 : twoChairsTablesNumber;
    fourChairsTablesNumber = (fourChairsTablesNumber > 3) ? 3 : fourChairsTablesNumber;
    setUpTables(scaleFactor, twoChairsTablesNumber, fourChairsTablesNumber);
}

TablesManager::~TablesManager() {
    for(TwoChairsTable* table : twoChairsTables) {
        delete table;
    }
    twoChairsTables.clear();

    for(FourChairsTable* table : fourChairsTables) {
        delete table;
    }
    fourChairsTables.clear();
}

void TablesManager::setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    int tableNumber = 0;
    for(int i = 0; i < twoChairsTablesNumber; i++) {
        tableNumber++;
        TwoChairsTable* newTable = new TwoChairsTable(scaleFactor, 
                                                      twoChairstablesTexturesPaths[i % (sizeof(twoChairstablesTexturesPaths) / 
                                                      sizeof(std::string))], 
                                                      twoChairsTablesPositions[i], 
                                                      twoChairsTablesDishesPositions[i],
                                                      twoChairsTablesHandlingPositions[i],
                                                      twoChairsTablesHandlingDirections[i],
                                                      tableNumber);
        twoChairsTables.push_back(newTable);
    }
    for(int i = 0; i < fourChairsTablesNumber; i++) {
        tableNumber++;
        FourChairsTable* newTable = new FourChairsTable(scaleFactor, 
                                                        fourChairstablesTexturesPaths[i % (sizeof(fourChairstablesTexturesPaths) / 
                                                        sizeof(std::string))], 
                                                        fourChairsTablesPositions[i], 
                                                        fourChairsTablesDishesPositions[i],
                                                        fourChairsTablesHandlingPositions[i],
                                                        fourChairsTablesHandlingDirections[i],
                                                        tableNumber);
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
        if(!table->getOccupiedStatus() && 
           !table->getWaitingToDishesTakenStatus()){
            return true;
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(!table->getOccupiedStatus() && 
           !table->getWaitingToDishesTakenStatus()) {
            return true;
        }
    }
    return false;
}

bool TablesManager::isTablesWaitingToHandling() {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getWaitingToHandleStatus()){
            return true;
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getWaitingToHandleStatus()) {
            return true;
        }
    }
    return false;
}

bool TablesManager::getTableOccupiedStatus(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getOccupiedStatus();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getOccupiedStatus();
        }
    }
    return false;
}

int TablesManager::getFreeTableNumber() {
    for(TwoChairsTable* table : twoChairsTables) {
        if(!table->getOccupiedStatus() && 
           !table->getWaitingToDishesTakenStatus()){
            return table->getTableNumber();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(!table->getOccupiedStatus() && 
           !table->getWaitingToDishesTakenStatus()) {
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

Positions TablesManager::getTableHandlingPositions(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getTableHandlingPositions();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getTableHandlingPositions();
        }
    }
    return Positions{-1.0f, -1.0f};
}

Directions TablesManager::getTableHandlingDirection(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getTableHandlingDirection();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getTableHandlingDirection();
        }
    }
    return Directions::DOWN;
}

Positions TablesManager::getDishesPositions(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getDishesPositions();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getDishesPositions();
        }
    }
    return Positions{-1.0f, -1.0f};
}

void TablesManager::occupyTableInstantly(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->occupyTableInstantly();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->occupyTableInstantly();
        }
    }
}

int TablesManager::getOccupiedChairsNumber(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getOccupiedChairsNumber();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getOccupiedChairsNumber();
        }
    }
    return -1;
}

bool TablesManager::checkIsLastCustomerOnTable(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            return table->getOccupiedStatus();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            return table->getOccupiedStatus();
        }
    }
    return false;
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

void TablesManager::freeInstantlyOccupiedTable(int tableNumber) {
     for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->resetTableOccupancy();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->resetTableOccupancy();
        }
    }
}

void TablesManager::setWaitingToHandling(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->waitToHandling();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->waitToHandling();
        }
    }
}

void TablesManager::resetWaitingToHandling(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->resetWaitingToHandling();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->resetWaitingToHandling();
        }
    }
}

bool TablesManager::isTablesWaitingToDishesTaken() {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getWaitingToDishesTakenStatus()){
            return true;
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getWaitingToDishesTakenStatus()) {
            return true;
        }
    }
    return false;
}

std::vector<int> TablesManager::getWaitingToHandlingTablesNumbers() {
    std::vector<int> waitingToHandlingTablesNumbers;
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getWaitingToHandleStatus()){
            waitingToHandlingTablesNumbers.push_back(table->getTableNumber());
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getWaitingToHandleStatus()) {
            waitingToHandlingTablesNumbers.push_back(table->getTableNumber());
        }
    }
    return waitingToHandlingTablesNumbers;
}

std::vector<int> TablesManager::getWaitingToDishesTakenTablesNumbers() {
    std::vector<int> waitingToDishesTakenTablesNumbers;
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getWaitingToDishesTakenStatus()){
            waitingToDishesTakenTablesNumbers.push_back(table->getTableNumber());
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getWaitingToDishesTakenStatus()) {
            waitingToDishesTakenTablesNumbers.push_back(table->getTableNumber());
        }
    }
    return waitingToDishesTakenTablesNumbers;
}

void TablesManager::setWaitingToDishesTaken(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->waitToDishesTaken();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->waitToDishesTaken();
        }
    }
}

void TablesManager::resetWaitingToDishesTaken(int tableNumber) {
    for(TwoChairsTable* table : twoChairsTables) {
        if(table->getTableNumber() == tableNumber){
            table->resetWaitingToDishesTaken();
        }
    }
    for(FourChairsTable* table : fourChairsTables) {
        if(table->getTableNumber() == tableNumber) {
            table->resetWaitingToDishesTaken();
        }
    }
}

std::vector<Table*> TablesManager::getTables() {
    std::vector<Table*> tables;
    tables.reserve(twoChairsTables.size() + fourChairsTables.size());
    for(TwoChairsTable* table : twoChairsTables) {
        tables.push_back(table);
    }
    for(FourChairsTable* table : fourChairsTables) {
        tables.push_back(table);
    }
    return tables;
}