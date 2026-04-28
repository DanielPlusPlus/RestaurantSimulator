#pragma once

#include "structures/ChairPositionsAndDirections.hpp"

#include <SFML/Graphics.hpp>


class Table {
protected:
    sf::Texture tableTexture;
    sf::Sprite tableSprite;
    int tableNumber = 0;
    int occupiedChairs = 0;
    Positions tableHandlingPositions;
    enum Directions tableHandlingDirection;
    bool isOccupied = false;
    bool isWaitingToHandling = false;
    bool isWaitingToDishesTaken = false;

    virtual bool loadTexture(int scaleFactor, std::string texturePath) = 0;
public:
    Table(int tableNumber, Positions tableHandlingPositions, 
          Directions tableHandlingDirection) : 
          tableNumber(tableNumber), 
          tableHandlingPositions(tableHandlingPositions),
          tableHandlingDirection(tableHandlingDirection) {};
    virtual ChairPositionsAndDirections occupyChairAndGetPositionsAndDirections() = 0;
    virtual void resetChairOccupancy(Directions chairHorizontalDirection, 
                                     Directions chairVerticalDirection) = 0;
    virtual void render(sf::RenderWindow* window) = 0;
    virtual Positions getDishesPositions() = 0;
    int getTableNumber() {
        return tableNumber;
    }
    int getOccupiedChairsNumber() {
        return occupiedChairs;
    }
    bool getOccupiedStatus() {
        return isOccupied;
    };
    void resetTableOccupancy() {
        isOccupied = false;
    }
    Positions getTableHandlingPositions() {
        return tableHandlingPositions;
    }
    Directions getTableHandlingDirection() {
        return tableHandlingDirection;
    }
    void occupyTableInstantly() {
        isOccupied = true;
    }
    void waitToHandling() {
        isWaitingToHandling = true;
    }
    bool getWaitingToHandleStatus() {
        return isWaitingToHandling;
    }
    void resetWaitingToHandling() {
        isWaitingToHandling = false;
    }
    void waitToDishesTaken() {
        isWaitingToDishesTaken = true;
    }
    bool getWaitingToDishesTakenStatus() {
        return isWaitingToDishesTaken;
    }
    void resetWaitingToDishesTaken() {
        isWaitingToDishesTaken = false;
    }
};