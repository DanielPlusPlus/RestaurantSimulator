#include "interiors/FourChairsTable.hpp"


FourChairsTable::FourChairsTable(int scaleFactor, std::string texturePath, 
                                 FourChairsTablesPositions chairsPositions, 
                                 FourChairsTablesDishesPositions dishesPositions,
                                 Positions tableHandlingPositions,
                                 int tableNumber) : 
                                 Table(tableNumber, tableHandlingPositions),
                                 chairsPositions(chairsPositions), 
                                 dishesPositions(dishesPositions) {
    loadTexture(scaleFactor, texturePath);
}

bool FourChairsTable::loadTexture(int scaleFactor, std::string texturePath) {
    if(!tableTexture.loadFromFile(texturePath))
        return false;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

ChairPositionsAndDirections FourChairsTable::occupyChairAndGetPositionsAndDirections() {
    if(availableChairs > 0) {
        availableChairs--;
        occupiedChairs++;
        if(availableChairs == 0) {
            isOccupied = true;
            isWaitingToHandling = true;
        }
        if(!isDownLeftChairOccupied) {
            isDownLeftChairOccupied = true;
            return chairsPositions.downLeftChairPositionsAndDirections;
        }
        else if(!isDownRightChairOccupied) {
            isDownRightChairOccupied = true;
            return chairsPositions.downRightChairPositionsAndDirections;
        }
        else if(!isUpLeftChairOccupied) {
            isUpLeftChairOccupied = true;
            return chairsPositions.upLeftChairPositionsAndDirections;
        }
        else if(!isUpRightChairOccupied) {
            isUpRightChairOccupied = true;
            return chairsPositions.upRightChairPositionsAndDirections;
        }
    }
    return ChairPositionsAndDirections{Positions{-1.0f, -1.0f}, Positions{-1.0f, -1.0f}, 
                                       Directions::RIGHT, Directions::DOWN};
}

Positions FourChairsTable::getDishesPositions() {
    dishPositionIndex++;
    if(dishPositionIndex == 1) {
        return dishesPositions.downLeftDish;
    }
    else if(dishPositionIndex == 2) {
        return dishesPositions.downRightDish;
    }
    else if(dishPositionIndex == 3) {
        return dishesPositions.upLeftDish;
    }
    else if(dishPositionIndex == 4) {
        return dishesPositions.upRightDish;
    }
    return Positions{-1.0f, -1.0f};
}

void FourChairsTable::resetChairOccupancy(Directions chairHorizontalDirection, 
                                          Directions chairVerticalDirection) {
    availableChairs++;
    occupiedChairs--;
    if(availableChairs == 4) {
        dishPositionIndex = 0;
        isOccupied = false;
        isWaitingToHandling = false;
        isWaitingToDishesTaken = true;
    }
    if(chairHorizontalDirection == Directions::LEFT && 
       chairVerticalDirection == Directions::DOWN) {
        isDownLeftChairOccupied = false;
    }
    else if(chairHorizontalDirection == Directions::RIGHT && 
            chairVerticalDirection == Directions::DOWN) {
        isDownRightChairOccupied = false;
    }
    else if(chairHorizontalDirection == Directions::LEFT && 
            chairVerticalDirection == Directions::UP) {
        isUpLeftChairOccupied = false;
    }
    else if(chairHorizontalDirection == Directions::RIGHT && 
            chairVerticalDirection == Directions::UP) {
        isUpRightChairOccupied = false;
    }
}

void FourChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
