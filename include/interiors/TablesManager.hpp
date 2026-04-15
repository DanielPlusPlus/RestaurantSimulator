#pragma once

#include "TwoChairsTable.hpp"
#include "FourChairsTable.hpp"
#include "structures/TwoChairsTablesPositions.hpp"
#include "structures/FourChairsTablesPositions.hpp"

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
    TwoChairsTablesPositions twoChairsTablesPositions[8] = {
        TwoChairsTablesPositions(55.0f, 130.0f, 86.0f, 130.0f,
                                 55.0f, 152.0f, 86.0f, 152.0f),
        TwoChairsTablesPositions(179.0f, 130.0f, 209.0f, 130.0f,
                                 179.0f, 152.0f, 209.0f, 152.0f),
        TwoChairsTablesPositions(7.0f, 130.0f, 37.0f, 130.0f,
                                 7.0f, 152.0f, 37.0f, 152.0f),
        TwoChairsTablesPositions(7.0f, 101.0f, 37.0f, 101.0f,
                                 7.0f, 120.0f, 37.0f, 120.0f),
        TwoChairsTablesPositions(7.0f, 72.0f, 37.0f, 72.0f,
                                 7.0f, 88.0f, 37.0f, 88.0f),
        TwoChairsTablesPositions(104.0f, 72.0f, 134.0f, 72.0f,
                                 104.0f, 88.0f, 134.0f, 88.0f),
        TwoChairsTablesPositions(160.0f, 9.0f, 190.0f, 9.0f,
                                 160.0f, 24.0f, 190.0f, 24.0f),
        TwoChairsTablesPositions(239.0f, 9.0f, 269.0f, 9.0f,
                                 239.0f, 24.0f, 269.0f, 24.0f)
    };
    FourChairsTablesPositions fourChairsTablesPositions[3] = {
        FourChairsTablesPositions(227.0f, 132.0f, 279.0f, 132.0f, 227.0f, 120.0f, 279.0f, 120.0f,
                                  227.0f, 152.0f, 279.0f, 152.0f, 227.0f, 104.0f, 279.0f, 104.0f),
        FourChairsTablesPositions(227.0f, 91.0f, 279.0f, 91.0f, 227.0f, 79.0f, 279.0f, 79.0f,
                                  227.0f, 104.0f, 279.0f, 104.0f, 227.0f, 72.0f, 279.0f, 72.0f),
        FourChairsTablesPositions(227.0f, 50.0f, 279.0f, 50.0f, 227.0f, 38.0f, 279.0f, 38.0f,
                                  227.0f, 72.0f, 279.0f, 72.0f, 227.0f, 24.0f, 279.0f, 24.0f)
    };

    std::vector<TwoChairsTable*> twoChairsTables;
    std::vector<FourChairsTable*> fourChairsTables;
public:
    TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void removeTable();
    void render(sf::RenderWindow* window);
};