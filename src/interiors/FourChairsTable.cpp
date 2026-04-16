#include "interiors/FourChairsTable.hpp"


FourChairsTable::FourChairsTable(int scaleFactor, std::string texturePath, FourChairsTablesPositions chairsPositions, int tableNumber) : 
                                 Table(tableNumber), chairsPositions(chairsPositions) {
    loadTexture(scaleFactor, texturePath);
}

bool FourChairsTable::loadTexture(int scaleFactor, std::string texturePath) {
    if(!tableTexture.loadFromFile(texturePath))
        return false;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

ChairPositionsAndDirection FourChairsTable::occupyChairAndGetPositions() {
    if(availableChairs > 0) {
        availableChairs--;
        if(availableChairs == 0) {
            isOccupied = true;
        }
        if(!isDownLeftChairOccupied) {
            isDownLeftChairOccupied = true;
            return chairsPositions.downLeftChairPositionsAndDirection;
        }
        else if(!isDownRightChairOccupied) {
            isDownRightChairOccupied = true;
            return chairsPositions.downRightChairPositionsAndDirection;
        }
        else if(!isUpLeftChairOccupied) {
            isUpLeftChairOccupied = true;
            return chairsPositions.upLeftChairPositionsAndDirection;
        }
        else if(!isUpRightChairOccupied) {
            isUpRightChairOccupied = true;
            return chairsPositions.upRightChairPositionsAndDirection;
        }
    }
    return ChairPositionsAndDirection{Positions{-1.0f, -1.0f}, Positions{-1.0f, -1.0f}, Directions::RIGHT};
}

void FourChairsTable::resetTableOccupancy() {
    availableChairs = 4;
    isDownLeftChairOccupied = false;
    isDownRightChairOccupied = false;
    isUpLeftChairOccupied = false;
    isUpRightChairOccupied = false;
    isOccupied = false;
}

void FourChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
