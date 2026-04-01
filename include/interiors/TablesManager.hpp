#pragma once

#include "Table.hpp"

#include <queue>
#include <SFML/Graphics.hpp>


class TablesManager {
private:
    const std::string twoChairstablesTextures[8] = {
        "assets/interiors/tables/table2_1.png",
        "assets/interiors/tables/table2_2.png",
        "assets/interiors/tables/table2_3.png",
        "assets/interiors/tables/table2_4.png",
        "assets/interiors/tables/table2_5.png",
        "assets/interiors/tables/table2_6.png",
        "assets/interiors/tables/table2_7.png",
        "assets/interiors/tables/table2_8.png"
    };
    const std::string fourChairstablesTextures[3] = {
        "assets/interiors/tables/table4_1.png",
        "assets/interiors/tables/table4_2.png",
        "assets/interiors/tables/table4_3.png"
    };
    std::vector<Table*> twoChairsTables;
    std::vector<Table*> fourChairsTables;
public:
    TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void removeTable();
    void render(sf::RenderWindow* window);
};