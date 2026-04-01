#include "items/Dish.hpp"


Dish::Dish(int scaleFactor, std::string texturePath, float xPos, float yPos, int tableNumber) : 
           xPos(xPos), yPos(yPos), tableNumber(tableNumber) {
    // texturesLoaded = loadTexture(scaleFactor, texturePath);
    loadTexture(scaleFactor, texturePath);
}

bool Dish::loadTexture(int scaleFactor, std::string texturePath) {
    if(!dishTexture.loadFromFile(texturePath)) {
        return false;
    }
    dishSprite.setTexture(dishTexture);
    dishSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));
    return true;
}

void Dish::render(sf::RenderWindow* window) {
    dishSprite.setPosition(xPos, yPos);
    window->draw(dishSprite);
}