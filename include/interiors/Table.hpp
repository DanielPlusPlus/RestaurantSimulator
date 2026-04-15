#pragma once

#include "structures/Positions.hpp"

#include <utility>
#include <SFML/Graphics.hpp>


class Table {
protected:
    sf::Texture tableTexture;
    sf::Sprite tableSprite;
    int tableNumber = 0;
    bool isOccupied = false;

    virtual bool loadTexture(int scaleFactor, std::string texturePath) = 0;
public:
    Table(int tableNumber) : tableNumber(tableNumber) {};
    virtual std::pair<Positions, Positions> occupyChairAndGetPositions() = 0;
    virtual void resetTableOccupancy() = 0;
    virtual void render(sf::RenderWindow* window) = 0;
    int getTableNumber() {
        return tableNumber;
    }
    bool getOccupiedStatus() {
        return isOccupied;
    };
};