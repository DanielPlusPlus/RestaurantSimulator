#pragma once

#include <SFML/Graphics.hpp>


class Table {
protected:
    sf::Texture tableTexture;
    sf::Sprite tableSprite;
    int tableNumber = 0;

    virtual bool loadTexture(int scaleFactor, std::string texturePath) = 0;
public:
    Table(int tableNumber) : tableNumber(tableNumber) {};
    virtual void render(sf::RenderWindow* window) = 0;
};