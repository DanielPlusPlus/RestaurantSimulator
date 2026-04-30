#pragma once

#include "structures/Positions.hpp"

#include <SFML/Graphics.hpp>


class Dish {
private:
    sf::Texture dishTexture;
    sf::Sprite dishSprite;
    Positions positions;
    int tableNumber = 0;

    bool loadTexture(int scaleFactor, std::string texturePath);
public:
    Dish(int scaleFactor, std::string texturePath, Positions positions, int tableNumber);
    int getTableNumber() {
        return tableNumber;
    }
    float getYPos() {
        return positions.yPos;
    }
    void changePositions(Positions newPositions) {
        positions = newPositions;
    }
    void render(sf::RenderWindow* window);
};