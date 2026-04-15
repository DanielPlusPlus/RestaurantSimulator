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

void TwoChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
