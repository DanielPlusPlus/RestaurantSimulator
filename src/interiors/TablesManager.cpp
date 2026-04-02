#include "interiors/TablesManager.hpp"

TablesManager::TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    twoChairsTablesNumber = (twoChairsTablesNumber > 8) ? 8 : twoChairsTablesNumber;
    fourChairsTablesNumber = (fourChairsTablesNumber > 3) ? 3 : fourChairsTablesNumber;
    setUpTables(scaleFactor, twoChairsTablesNumber, fourChairsTablesNumber);
}

void TablesManager::setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber) {
    for(int i = 0; i < twoChairsTablesNumber; i++) {
        TwoChairsTable* newTable = new TwoChairsTable(scaleFactor, twoChairstablesTexturesPaths[i % (sizeof(twoChairstablesTexturesPaths) / sizeof(std::string))], 
                                    i + 1);
        twoChairsTables.push_back(newTable);
    }
    for(int i = 0; i < fourChairsTablesNumber; i++) {
        FourChairsTable* newTable = new FourChairsTable(scaleFactor, fourChairstablesTexturesPaths[i % (sizeof(fourChairstablesTexturesPaths) / sizeof(std::string))], 
                                    i + 1);
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
    for(TwoChairsTable* table : twoChairsTables) {
        table->render(window);
    }
    for(FourChairsTable* table : fourChairsTables) {
        table->render(window);
    }
}