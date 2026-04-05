#include "characters/CharactersManager.hpp"

#include <random>
#include <algorithm>


CharactersManager::CharactersManager(int scaleFactor, float tileWidth, float tileHeight, int chefsNumber, 
                                     int waitersNumber, DishesManager* dishesManager) {
    moveXSpeed = tileWidth;
    moveYSpeed = tileHeight;
    
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

void CharactersManager::addCustomer(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> customerTextureDist(0, 1);
    Customer* newCustomer = new Customer(scaleFactor, customersTexturesPaths[customerTextureDist(globalRNG)], tileWidth, 
                                         tileHeight, moveXSpeed, moveYSpeed, waitingCustomers.size() + 1, 
                                         customersStartPosition, rightDoorPosition);
    waitingCustomers.push_back(newCustomer);

    std::uniform_real_distribution<float> timeToAddCustomerDist(10.0f, 20.0f);
    timeToAddCustomer = timeToAddCustomerDist(globalRNG);
}

void CharactersManager::removeCustomer() {
    
}

void CharactersManager::update(float deltaTime, int scaleFactor, float tileWidth, float tileHeight) {
    addCustomerTimer += deltaTime;
    if(addCustomerTimer > timeToAddCustomer) {
        addCustomerTimer = 0.0f;
        addCustomer(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed);
    }
    
    std::sort(chefs.begin(), chefs.end(), [](Chef* chef1, Chef* chef2) -> bool{
        return chef1->getYPos() < chef2->getYPos();
    });
    for(Chef* chef : chefs) {
        chef->update(deltaTime, scaleFactor);
    }
    for(Customer* customer : waitingCustomers) {
        customer->update(deltaTime, scaleFactor);
    }
}

void CharactersManager::render(sf::RenderWindow* window) {
    for(Chef* chef : chefs) {
        chef->render(window);
    }
    for(Customer* customer : waitingCustomers) {
        customer->render(window);
    }
}