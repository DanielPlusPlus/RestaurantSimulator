#include "interiors/FourChairsTable.hpp"

FourChairsTable::FourChairsTable(int scaleFactor, std::string texturePath, int tableNumber) : 
             Table(tableNumber) {
    loadTexture(scaleFactor, texturePath);
}

bool FourChairsTable::loadTexture(int scaleFactor, std::string texturePath) {
    if(!tableTexture.loadFromFile(texturePath))
        return false;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

void FourChairsTable::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}
