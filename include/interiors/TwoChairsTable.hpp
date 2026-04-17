#pragma once

#include "Table.hpp"
#include "structures/TwoChairsTablesPositions.hpp"

#include <SFML/Graphics.hpp>


class TwoChairsTable : public Table {
private:
    TwoChairsTablesPositions chairsPositions;
    int availableChairs = 2;
    bool isLeftChairOccupied = false;
    bool isRightChairOccupied = false;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    TwoChairsTable(int scaleFactor, std::string texturePath, 
                   TwoChairsTablesPositions chairsPositions,
                   int tableNumber);
    ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() override;
    TwoChairsTablesPositions getChairsPositions() {
        return chairsPositions;
    }
    void resetChairOccupancy(Directions chairHorizontalDirection, 
                             Directions chairVerticalDirection) override;
    void render(sf::RenderWindow* window) override;
};