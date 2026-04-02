#pragma once

#include "Table.hpp"

#include <SFML/Graphics.hpp>


class FourChairsTable : public Table {
private:
    bool loadTexture(int scaleFactor, std::string texturePath) override;
public:
    FourChairsTable(int scaleFactor, std::string texturePath, int tableNumber);
    void render(sf::RenderWindow* window) override;
};