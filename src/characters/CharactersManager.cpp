#include "characters/CharactersManager.hpp"
#include "characters/Chef.hpp"
#include "characters/Waiter.hpp"
#include "characters/Customer.hpp"

#include <random>
#include <algorithm>
#include <iostream>

CharactersManager::CharactersManager(int scaleFactor, float tileWidth, float tileHeight, int chefsNumber, 
                                     int waitersNumber, DishesManager* dishesManager) : 
                                     timeToAddCustomerDist(10.0f, 20.0f),
                                     timeToRemoveCustomerDist(20.0f, 40.0f) {
    moveXSpeed = tileWidth;
    moveYSpeed = tileHeight;

    extern std::mt19937 globalRNG;
    timeToRemoveWaitingCustomer = timeToRemoveCustomerDist(globalRNG);
    
    addChefs(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, chefsNumber, dishesManager);
    addWaiters(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, waitersNumber);
}

void CharactersManager::addChefs(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed, 
                                 int chefsNumber, DishesManager* dishesManager) {
    for(int i = 0; i < chefsNumber; i++) {
        Chef* newChef = new Chef(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, i + 1, 
                                 chefsStartPositions[i], chefsStartDirections[i], dishesManager);
        chefs.push_back(newChef);
    }
}

void CharactersManager::addWaiters(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed, 
                                   int waitersNumber) {
    for(int i = 0; i < waitersNumber; i++) {
        Waiter* newWaiter = new Waiter(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, i + 1, 
                                       waitersStartPositions[i], waiterQueueHandlingPositions, 
                                       waiterDishPickupPositions, waiterDishDropoffPositions);
        waiters.push_back(newWaiter);
    }
}

void CharactersManager::addCustomer(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> customerTextureDist(0, 1);
    Customer* newCustomer = new Customer(scaleFactor, customersTexturesPaths[customerTextureDist(globalRNG)], tileWidth, 
                                         tileHeight, moveXSpeed, moveYSpeed, waitingCustomers.size() + 1, 
                                         customersStartPositions, customersQueueStartingPositions);
    waitingCustomers.push_back(newCustomer);
    timeToAddCustomer = timeToAddCustomerDist(globalRNG);
}

void CharactersManager::moveWaitingCustomerToResignation() {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> waitingCustomerIndex(5, waitingCustomers.size() - 1);
    int index = waitingCustomerIndex(globalRNG);
    if(index >= 0 && index < waitingCustomers.size()) {
        Customer* customer = waitingCustomers[index];
        customer->setResigning(true);
        resigningCustomers.push_back(customer);
        waitingCustomers.erase(waitingCustomers.begin() + index);
    }
    timeToRemoveWaitingCustomer = timeToRemoveCustomerDist(globalRNG);
}

void CharactersManager::removeResigningCustomer(int index) {
    if(index >= 0 && index < resigningCustomers.size()) {
        delete resigningCustomers[index];
        resigningCustomers.erase(resigningCustomers.begin() + index);
    }
}

void CharactersManager::update(float deltaTime, int scaleFactor, float tileWidth, 
                               float tileHeight, Level* level) {
    addCustomerTimer += deltaTime;
    if(addCustomerTimer > timeToAddCustomer) {
        addCustomerTimer = 0.0f;
        addCustomer(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed);
    }
    if(waitingCustomers.size() > 5) {
        removeWatingCustomerTimer += deltaTime;
        if(removeWatingCustomerTimer > timeToRemoveWaitingCustomer) {
            removeWatingCustomerTimer = 0.0f;
            moveWaitingCustomerToResignation();
        }
    }
    
    std::sort(chefs.begin(), chefs.end(), [](Chef* chef1, Chef* chef2) -> bool{
        return chef1->getYPos() < chef2->getYPos();
    });
    for(Chef* chef : chefs) {
        chef->update(deltaTime, scaleFactor);
    }
    for (Waiter* waiter : waiters) {
        waiter->update(deltaTime, scaleFactor, level);
    }
    for(int i = 0; i < waitingCustomers.size(); i++) {
        if(i == 0) {
            waitingCustomers[i]->updateIfWaiting(deltaTime, scaleFactor, 
                                                 customersQueueStartingPositions.xPos * scaleFactor);
        }
        else {
            waitingCustomers[i]->updateIfWaiting(deltaTime, scaleFactor, waitingCustomers[i - 1]->getXPos() + tileWidth);
        }
    }
    for(int i = resigningCustomers.size() - 1; i >= 0; i--) {
        if(resigningCustomers[i]->getAssignedToRemoveStatus()) {
            removeResigningCustomer(i);
        }
        resigningCustomers[i]->updateIfResigning(deltaTime, scaleFactor);
    }
}

void CharactersManager::renderChefs(sf::RenderWindow* window) {
    for(Chef* chef : chefs) {
        chef->render(window);
    }
}

void CharactersManager::renderWaitersAndCustomers(sf::RenderWindow* window) {
    for(Waiter* waiter : waiters) {
        waiter->render(window);
    }
    for(Customer* waitingCustomer : waitingCustomers) {
        waitingCustomer->render(window);
    }
    for(Customer* resigningCustomer : resigningCustomers) {
        resigningCustomer->render(window);
    }
}