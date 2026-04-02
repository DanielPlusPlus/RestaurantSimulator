#pragma once

#include "Table.hpp"
#include "structures/TwoChairsTablesPositions.hpp"

#include <SFML/Graphics.hpp>


class TwoChairsTable : public Table {
private:
    TwoChairsTablesPositions chairsPositions;
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    TwoChairsTable(int scaleFactor, std::string texturePath, TwoChairsTablesPositions chairsPositions,
                   int tableNumber);
    void render(sf::RenderWindow* window) override;
};