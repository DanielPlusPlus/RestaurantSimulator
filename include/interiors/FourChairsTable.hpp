#pragma once

#include "Table.hpp"
#include "structures/FourChairsTablesPositions.hpp"
#include "structures/FourChairsTablesDishesPositions.hpp"

#include <SFML/Graphics.hpp>


class FourChairsTable : public Table {
private:
    FourChairsTablesPositions chairsPositions;
    FourChairsTablesDishesPositions dishesPositions;
    int availableChairs = 4;
    int dishPositionIndex = 0;
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
                    Directions tableHandlingDirection,
                    int tableNumber);
    ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() override;
    FourChairsTablesPositions getChairsPositions() {
        return chairsPositions;
    }
    Positions getDishesPositions() override;
    void resetChairOccupancy(Directions chairHorizontalDirection, 
                             Directions chairVerticalDirection) override;
    void render(sf::RenderWindow* window) override;
};