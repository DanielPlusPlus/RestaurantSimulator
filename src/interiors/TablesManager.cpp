#include "interiors/TablesManager.hpp"

TablesManager::TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    twoChairsTablesNumber = (twoChairsTablesNumber > 8) ? 8 : twoChairsTablesNumber;
    fourChairsTablesNumber = (fourChairsTablesNumber > 3) ? 3 : fourChairsTablesNumber;
    setUpTables(scaleFactor, twoChairsTablesNumber, fourChairsTablesNumber);
}

void TablesManager::setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    for(int i = 0; i < twoChairsTablesNumber; i++) {
        Table* newTable = new Table(scaleFactor, twoChairstablesTextures[i % (sizeof(twoChairstablesTextures) / sizeof(std::string))], 
                                    i + 1, 2);
        twoChairsTables.push_back(newTable);
    }
    for(int i = 0; i < fourChairsTablesNumber; i++) {
        Table* newTable = new Table(scaleFactor, fourChairstablesTextures[i % (sizeof(fourChairstablesTextures) / sizeof(std::string))], 
                                    i + 1, 4);
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

void TablesManager::render(sf::RenderWindow* window) {
    for(Table* table : twoChairsTables) {
        table->render(window);
    }
    for(Table* table : fourChairsTables) {
        table->render(window);
    }
}