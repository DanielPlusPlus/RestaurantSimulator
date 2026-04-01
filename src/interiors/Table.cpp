#include "interiors/Table.hpp"

Table::Table(int scaleFactor, std::string texturePath, int tableNumber, int numberOfSeats) : 
             tableNumber(tableNumber), numberOfSeats(numberOfSeats) {
    loadTexture(scaleFactor, texturePath);
}

bool Table::loadTexture(int scaleFactor, std::string texturePath) {
    if(!tableTexture.loadFromFile(texturePath))
        return false;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

void Table::render(sf::RenderWindow* window) {
    window->draw(tableSprite);
}

