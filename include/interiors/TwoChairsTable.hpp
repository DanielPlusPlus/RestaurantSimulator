#pragma once

#include "Table.hpp"
#include "structures/TwoChairsTablesPositions.hpp"

#include <SFML/Graphics.hpp>


class TwoChairsTable : public Table {
private:
    TablesTypesEnum tableType = TablesTypesEnum::TWO_CHAIRS_TABLE;
    TwoChairsTablesPositions chairsPositions;
    Positions dishesPositions;
    int availableChairs = 2;
    bool isLeftChairOccupied = false;
    bool isRightChairOccupied = false;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    TwoChairsTable(int scaleFactor, std::string texturePath, 
                   TwoChairsTablesPositions chairsPositions,
                   Positions dishesPositions, 
                   Positions tableHandlingPositions,
                   int tableNumber);
    ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() override;
    TwoChairsTablesPositions getChairsPositions() {
        return chairsPositions;
    }
    Positions getDishesPositions() {
        return dishesPositions;
    }
    void resetChairOccupancy(Directions chairHorizontalDirection, 
                             Directions chairVerticalDirection) override;
    void render(sf::RenderWindow* window) override;
};