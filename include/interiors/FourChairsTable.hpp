#pragma once

#include "Table.hpp"
#include "structures/FourChairsTablesPositions.hpp"

#include <SFML/Graphics.hpp>


class FourChairsTable : public Table {
private:
    FourChairsTablesPositions chairsPositions;
    int availableChairs = 4;
    bool isDownLeftChairOccupied = false;
    bool isDownRightChairOccupied = false;
    bool isUpLeftChairOccupied = false;
    bool isUpRightChairOccupied = false;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    FourChairsTable(int scaleFactor, std::string texturePath, 
                    FourChairsTablesPositions chairsPositions, 
                    int tableNumber);
    ChairPositionsAndDirection occupyChairAndGetPositions() override;
    void resetTableOccupancy() override;
    void render(sf::RenderWindow* window) override;
};