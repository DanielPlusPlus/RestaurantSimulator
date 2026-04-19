#pragma once

#include "structures/ChairPositionsAndDirections.hpp"
#include "enums/TablesTypesEnum.hpp"

#include <SFML/Graphics.hpp>


class Table {
protected:
    sf::Texture tableTexture;
    sf::Sprite tableSprite;
    int tableNumber = 0;
    TablesTypesEnum tableType;
    bool isOccupied = false;

    virtual bool loadTexture(int scaleFactor, std::string texturePath) = 0;
public:
    Table(int tableNumber) : tableNumber(tableNumber) {};
    virtual ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() = 0;
    virtual void resetChairOccupancy(Directions chairHorizontalDirection, 
                                     Directions chairVerticalDirection) = 0;
    virtual void occupyTableInstantly() = 0;
    virtual void render(sf::RenderWindow* window) = 0;
    int getTableNumber() {
        return tableNumber;
    }
    bool getOccupiedStatus() {
        return isOccupied;
    };
    void resetTableOccupancy() {
        isOccupied = false;
    }
    TablesTypesEnum getTableType() {
        return tableType;
    }
};