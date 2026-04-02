#pragma once

#include "Table.hpp"
#include "structures/FourChairsTablesPositions.hpp"

#include <SFML/Graphics.hpp>


class FourChairsTable : public Table {
private:
    FourChairsTablesPositions chairsPositions;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    FourChairsTable(int scaleFactor, std::string texturePath, FourChairsTablesPositions chairsPositions,
                    int tableNumber);
    void render(sf::RenderWindow* window) override;
};