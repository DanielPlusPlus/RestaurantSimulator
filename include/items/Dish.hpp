#pragma once

#include "structures/Positions.hpp"

#include <SFML/Graphics.hpp>


class Dish {
private:
    sf::Texture dishTexture;
    sf::Sprite dishSprite;
    Positions positions{0.0f, 0.0f};
    int tableNumber = 0;

    bool loadTexture(int scaleFactor, std::string texturePath);
public:
    Dish(int scaleFactor, std::string texturePath, Positions positions, int tableNumber);
    void render(sf::RenderWindow* window);
};