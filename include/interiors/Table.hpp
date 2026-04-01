#pragma once

#include <SFML/Graphics.hpp>


class Table {
private:
    sf::Texture tableTexture;
    sf::Sprite tableSprite;
    int tableNumber = 0;
    int numberOfSeats = 2;

    bool loadTexture(int scaleFactor, std::string texturePath);
public:
    Table(int scaleFactor, std::string texturePath, int tableNumber, int numberOfSeats);
    void render(sf::RenderWindow* window);
};