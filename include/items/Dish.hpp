#pragma once

#include <SFML/Graphics.hpp>


class Dish {
private:
    sf::Texture dishTexture;
    sf::Sprite dishSprite;
    float xPos = 0.0f;
    float yPos = 0.0f;
    int tableNumber = 0;

    bool loadTexture(int scaleFactor, std::string texturePath);
public:
    Dish(int scaleFactor, std::string texturePath, float xPos, float yPos, int tableNumber);
    void render(sf::RenderWindow* window);
};