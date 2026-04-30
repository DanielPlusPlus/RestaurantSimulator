#pragma once

#include "TwoChairsTable.hpp"
#include "FourChairsTable.hpp"
#include "structures/TwoChairsTablesPositions.hpp"
#include "structures/FourChairsTablesPositions.hpp"
#include "structures/FourChairsTablesDishesPositions.hpp"

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
    const TwoChairsTablesPositions twoChairsTablesPositions[8] = {
        TwoChairsTablesPositions(55.0f, 130.0f, 86.0f, 130.0f,
                                 55.0f, 152.0f, 86.0f, 152.0f),
        TwoChairsTablesPositions(179.0f, 130.0f, 209.0f, 130.0f,
                                 179.0f, 152.0f, 209.0f, 152.0f),
        TwoChairsTablesPositions(7.0f, 130.0f, 37.0f, 130.0f,
                                 7.0f, 152.0f, 37.0f, 152.0f),
        TwoChairsTablesPositions(7.0f, 101.0f, 37.0f, 101.0f,
                                 7.0f, 112.0f, 37.0f, 112.0f),
        TwoChairsTablesPositions(7.0f, 72.0f, 37.0f, 72.0f,
                                 7.0f, 88.0f, 37.0f, 88.0f),
        TwoChairsTablesPositions(104.0f, 72.0f, 134.0f, 72.0f,
                                 104.0f, 88.0f, 134.0f, 88.0f),
        TwoChairsTablesPositions(160.0f, 9.0f, 190.0f, 9.0f,
                                 160.0f, 24.0f, 190.0f, 24.0f),
        TwoChairsTablesPositions(239.0f, 9.0f, 269.0f, 9.0f,
                                 239.0f, 24.0f, 269.0f, 24.0f)
    };
    const FourChairsTablesPositions fourChairsTablesPositions[3] = {
        FourChairsTablesPositions(227.0f, 132.0f, 279.0f, 132.0f, 227.0f, 120.0f, 279.0f, 120.0f,
                                  227.0f, 152.0f, 279.0f, 152.0f, 227.0f, 104.0f, 279.0f, 104.0f),
        FourChairsTablesPositions(227.0f, 91.0f, 279.0f, 91.0f, 227.0f, 79.0f, 279.0f, 79.0f,
                                  227.0f, 104.0f, 279.0f, 104.0f, 227.0f, 64.0f, 279.0f, 64.0f),
        FourChairsTablesPositions(227.0f, 50.0f, 279.0f, 50.0f, 227.0f, 38.0f, 279.0f, 38.0f,
                                  227.0f, 64.0f, 279.0f, 64.0f, 227.0f, 24.0f, 279.0f, 24.0f)
    };
    const Positions twoChairsTablesDishesPositions[8] = {
        Positions{70.5f, 142.0f},
        Positions{194.0f, 142.0f},
        Positions{22.0f, 142.0f},
        Positions{22.0f, 113.0f},
        Positions{22.0f, 84.0f},
        Positions{119.0f, 84.0f},
        Positions{175.0f, 21.0f},
        Positions{254.0f, 21.0f}
    };
    const FourChairsTablesDishesPositions fourChairsTablesDishesPositions[3] = {
        FourChairsTablesDishesPositions{244.0f, 147.0f, 262.0f, 147.0f, 244.0f, 132.0f, 262.0f, 132.0f},
        FourChairsTablesDishesPositions{244.0f, 106.0f, 262.0f, 106.0f, 244.0f, 91.0f, 262.0f, 91.0f},
        FourChairsTablesDishesPositions{244.0f, 65.0f, 262.0f, 65.0f, 244.0f, 50.0f, 262.0f, 50.0f}
    };
    const Positions twoChairsTablesHandlingPositions[8] = {
        Positions{70.5f, 112.0f},
        Positions{194.0f, 112.0f},
        Positions{22.0f, 112.0f},
        Positions{22.0f, 88.0f},
        Positions{22.0f, 88.0f},
        Positions{119.0f, 88.0f},
        Positions{175.0f, 24.0f},
        Positions{254.0f, 24.0f}
    };
    const Positions fourChairsTablesHandlingPositions[3] = {
        Positions{253.0f, 104.0f},
        Positions{253.0f, 64.0f},
        Positions{253.0f, 24.0f}
    };
    const enum Directions twoChairsTablesHandlingDirections[8] = {
        Directions::DOWN,
        Directions::DOWN,
        Directions::DOWN,
        Directions::DOWN,
        Directions::UP,
        Directions::UP,
        Directions::UP,
        Directions::UP
    };
    const enum Directions fourChairsTablesHandlingDirections[3] = {
        Directions::DOWN,
        Directions::DOWN,
        Directions::DOWN
    };

    std::vector<TwoChairsTable*> twoChairsTables;
    std::vector<FourChairsTable*> fourChairsTables;
public:
    TablesManager(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    ~TablesManager();
    void setUpTables(int scaleFactor, int twoChairsTablesNumber, int fourChairsTablesNumber);
    void removeTable();
    bool isFreeTable();
    bool isTablesWaitingToHandling();
    bool getTableOccupiedStatus(int tableNumber);
    int getFreeTableNumber();
    bool isFreeChair(int tableNumber);
    ChairPositionsAndDirections getFreeChairPositions(int tableNumber);
    Positions getTableHandlingPositions(int tableNumber);
    Directions getTableHandlingDirection(int tableNumber);
    Positions getDishesPositions(int tableNumber);
    void occupyTableInstantly(int tableNumber);
    int getOccupiedChairsNumber(int tableNumber);
    bool checkIsLastCustomerOnTable(int tableNumber);
    void freeChair(int tableNumber, 
                   Directions chairHorizontalDirection, 
                   Directions chairVerticalDirection);
    void freeInstantlyOccupiedTable(int tableNumber);
    void setWaitingToHandling(int tableNumber);
    void resetWaitingToHandling(int tableNumber);
    void setWaitingToDishesTaken(int tableNumber);
    void resetWaitingToDishesTaken(int tableNumber);
    bool isTablesWaitingToDishesTaken();
    std::vector<int> getWaitingToHandlingTablesNumbers();
    std::vector<int> getWaitingToDishesTakenTablesNumbers();
    void render(sf::RenderWindow* window);
    std::vector<Table*> getTables();
    Positions getTwoChairsTableDishesPositionsByNumber(int tableNumber);
};