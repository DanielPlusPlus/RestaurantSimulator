#include "interiors/TwoChairsTable.hpp"

TwoChairsTable::TwoChairsTable(int scaleFactor, std::string texturePath, TwoChairsTablesPositions chairsPositions, int tableNumber) : 
                               Table(tableNumber), chairsPositions(chairsPositions) {
    loadTexture(scaleFactor, texturePath);
}

bool TwoChairsTable::loadTexture(int scaleFactor, std::string texturePath) {
    if(!tableTexture.loadFromFile(texturePath))
        return false;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

ChairPositionsAndDirections TwoChairsTable::occupyChairAndGetPositionsAndDirections() {
    if(availableChairs > 0) {
        availableChairs--;
        if(availableChairs == 0) {
            isOccupied = true;
        }
        if(!isLeftChairOccupied) {
            isLeftChairOccupied = true;
            return chairsPositions.leftChairPositionsAndDirections;
        }
        else if(!isRightChairOccupied) {
            isRightChairOccupied = true;
            return chairsPositions.rightChairPositionsAndDirections;
        }
    }
    return ChairPositionsAndDirections{Positions{-1.0f, -1.0f}, Positions{-1.0f, -1.0f}, 
                                       Directions::RIGHT, Directions::DOWN};
}

void TwoChairsTable::resetChairOccupancy(Directions chairHorizontalDirection, 
                                         Directions chairVerticalDirection) {
    availableChairs++;
    if(availableChairs == 2) {
        isOccupied = false;
    }
    if(chairHorizontalDirection == Directions::LEFT) {
        isLeftChairOccupied = false;
    }
    else if(chairHorizontalDirection == Directions::RIGHT) {
        isRightChairOccupied = false;
    }
}

void TwoChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
