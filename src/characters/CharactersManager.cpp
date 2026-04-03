#include "characters/CharactersManager.hpp"

CharactersManager::CharactersManager(int scaleFactor, float tileWidth, float tileHeight, int chefsNumber, 
                                     int waitersNumber, DishesManager* dishesManager) {
    float moveXSpeed = tileWidth;
    float moveYSpeed = tileHeight;
    addChefs(scaleFactor, tileWidth, moveXSpeed, moveYSpeed, chefsNumber, chefsStartPositions[0], dishesManager);
}

void CharactersManager::addChefs(int scaleFactor, float tileWidth, float moveXSpeed, float moveYSpeed, 
                                 int chefsNumber, Positions positions, DishesManager* dishesManager) {
    for(int i = 0; i < chefsNumber; i++) {
        Chef* newChef = new Chef(scaleFactor, tileWidth, moveXSpeed, moveYSpeed, i + 1, 
                                 chefsStartPositions[i], dishesManager);
        chefs.push_back(newChef);
    }
}

void CharactersManager::addWaiters(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, int waitersNumber) {
    
}

void CharactersManager::addCustomer(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, 
                                    CharactersTexturesPaths texturesPaths) {
    
}

void CharactersManager::removeCustomer() {
    
}

void CharactersManager::update(float deltaTime, int scaleFactor) {
    for(Chef* chef : chefs) {
        chef->update(deltaTime, scaleFactor);
    }
}

void CharactersManager::render(sf::RenderWindow* window) {
    for(Chef* chef : chefs) {
        chef->render(window);
    }
}