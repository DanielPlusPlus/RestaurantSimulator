#pragma once

#include "TwoChairsTable.hpp"
#include "FourChairsTable.hpp"

#include <queue>
#include <SFML/Graphics.hpp>


class TablesManager {
private:
    const std::string twoChairstablesTexturesPaths[8] = {
        "assets/interiors/tables/table2_1.png",
        "assets/interiors/tables/table2_2.png",
        "assets/interiors/tables/table2_3.png",
        "assets/interiors/tables/table2_4.png",
        "assets/interiors/tables/table2_5.png",
        "assets/interiors/tables/table2_6.png",
        "assets/interiors/tables/table2_7.png",
        "assets/interiors/tables/table2_8.png"
    };
    const std::string fourChairstablesTexturesPaths[3] = {
        "assets/interiors/tables/table4_1.png",
        "assets/interiors/tables/table4_2.png",
        "assets/interiors/tables/table4_3.png"
    };
    std::vector<TwoChairsTable*> twoChairsTables;
    std::vector<FourChairsTable*> fourChairsTables;
public:
    TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void removeTable();
    void render(sf::RenderWindow* window);
};