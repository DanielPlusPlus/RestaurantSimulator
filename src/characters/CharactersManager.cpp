#include "characters/CharactersManager.hpp"

#include <algorithm>


CharactersManager::CharactersManager(int scaleFactor, float tileWidth, float tileHeight, int chefsNumber, 
                                     int waitersNumber, DishesManager* dishesManager) {
    float moveXSpeed = tileWidth;
    float moveYSpeed = tileHeight;
    addChefs(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, chefsNumber, dishesManager);
}

void CharactersManager::addChefs(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed, 
                                 int chefsNumber, DishesManager* dishesManager) {
    for(int i = 0; i < chefsNumber; i++) {
        Chef* newChef = new Chef(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, i + 1, 
                                 chefsStartPositions[i], chefsStartDirections[i], dishesManager);
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
    // std::sort(chefs.begin(), chefs.end(), [](Chef* chef1, Chef* chef2) -> bool{
    //     return chef1->getYPos() < chef2->getYPos();
    // });
    for(Chef* chef : chefs) {
        chef->update(deltaTime, scaleFactor);
    }
}

void CharactersManager::render(sf::RenderWindow* window) {
    for(Chef* chef : chefs) {
        chef->render(window);
    }
}