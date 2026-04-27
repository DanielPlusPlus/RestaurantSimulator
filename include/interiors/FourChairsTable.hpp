#pragma once

#include "Table.hpp"
#include "structures/FourChairsTablesPositions.hpp"
#include "structures/FourChairsTablesDishesPositions.hpp"

#include <SFML/Graphics.hpp>


class FourChairsTable : public Table {
private:
TablesTypesEnum tableType = TablesTypesEnum::FOUR_CHAIRS_TABLE;
    FourChairsTablesPositions chairsPositions;
    FourChairsTablesDishesPositions dishesPositions;
    int availableChairs = 4;
    bool isDownLeftChairOccupied = false;
    bool isDownRightChairOccupied = false;
    bool isUpLeftChairOccupied = false;
    bool isUpRightChairOccupied = false;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    FourChairsTable(int scaleFactor, std::string texturePath, 
                    FourChairsTablesPositions chairsPositions, 
                    FourChairsTablesDishesPositions dishesPositions, 
                    Positions tableHandlingPositions, 
                    int tableNumber);
    ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() override;
    FourChairsTablesPositions getChairsPositions() {
        return chairsPositions;
    }
    FourChairsTablesDishesPositions getDishesPositions() {
        return dishesPositions;
    }
    void resetChairOccupancy(Directions chairHorizontalDirection, 
                             Directions chairVerticalDirection) override;
    void render(sf::RenderWindow* window) override;
};