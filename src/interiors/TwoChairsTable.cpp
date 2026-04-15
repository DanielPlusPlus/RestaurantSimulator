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

std::pair<Positions, Positions> TwoChairsTable::occupyChairAndGetPositions() {
    if(availableChairs > 0) {
        availableChairs--;
        if(availableChairs == 0) {
            isOccupied = true;
        }
        if(!isLeftChairOccupied) {
            isLeftChairOccupied = true;
            return std::pair<Positions, Positions>(chairsPositions.leftChairPositions, 
                                                   chairsPositions.leftChairEnterPositions);
        }
        else if(!isRightChairOccupied) {
            isRightChairOccupied = true;
            return std::pair<Positions, Positions>(chairsPositions.rightChairPositions, 
                                                    chairsPositions.rightChairEnterPositions);
        }
    }
    return std::pair<Positions, Positions>(Positions{-1.0f, -1.0f}, Positions{-1.0f, -1.0f});
}

void TwoChairsTable::resetTableOccupancy() {
    availableChairs = 2;
    isLeftChairOccupied = false;
    isRightChairOccupied = false;
    isOccupied = false;
}

void TwoChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
