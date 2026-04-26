#include "characters/CharactersManager.hpp"
#include "characters/Chef.hpp"
#include "characters/Waiter.hpp"
#include "characters/Customer.hpp"
#include "interiors/TablesManager.hpp"

#include <random>
#include <algorithm>
#include <iostream> // do usunięcia


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

void CharactersManager::addChefs(int scaleFactor, float tileWidth, float tileHeight, 
                                 float moveXSpeed, float moveYSpeed, int chefsNumber, 
                                 DishesManager* dishesManager) {
    for(int i = 0; i < chefsNumber; i++) {
        Chef* newChef = new Chef(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed, i + 1, 
                                 chefsStartPositions[i], chefsStartDirections[i], dishesManager);
        chefs.push_back(newChef);
    }
}

void CharactersManager::addWaiters(int scaleFactor, float tileWidth, float tileHeight, 
                                   float moveXSpeed, float moveYSpeed, int waitersNumber) {
    for(int i = 0; i < waitersNumber; i++) {
        Waiter* newWaiter = new Waiter(scaleFactor, moveXSpeed, moveYSpeed, i + 1, 
                                       waitersStartPositions[i], waitersQueueHandlingPositions, 
                                       waitersDishPickupPositions, waitersDishDropoffPositions);
        waiters.push_back(newWaiter);
    }
}

void CharactersManager::addWaitingCustomer(int scaleFactor, float tileWidth, float tileHeight, 
                                           float moveXSpeed, float moveYSpeed) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> customerTextureDist(0, 1);
    Customer* newCustomer = new Customer(scaleFactor, customersTexturesPaths[customerTextureDist(globalRNG)], 
                                         tileWidth, tileHeight, moveXSpeed, moveYSpeed, 
                                         waitingCustomers.size() + 1, 
                                         customersStartPositions, customersQueueStartingPositions, 
                                         customersEnterRestaurantPositions, 
                                         customersExitRestaurantPositions);
    waitingCustomers.push_back(newCustomer);
    timeToAddCustomer = timeToAddCustomerDist(globalRNG);
}

void CharactersManager::moveWaitingCustomerToResignation() {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> waitingCustomerIndexDist(3, waitingCustomers.size() - 1);
    int index = waitingCustomerIndexDist(globalRNG);
    if(index >= 0 && index < waitingCustomers.size()) {
        Customer* customer = waitingCustomers[index];
        customer->changeToResigningState();
        resigningCustomers.push_back(customer);
        waitingCustomers.erase(waitingCustomers.begin() + index);
    }
    timeToRemoveWaitingCustomer = timeToRemoveCustomerDist(globalRNG);
}

void CharactersManager::moveWaitingCustomerToInside(int scaleFactor, int tableNumber, 
                                                    TablesManager* tablesManager) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> instantTableOccupationDist(1, 4); // do poprawy
    int instantTableOccupation = instantTableOccupationDist(globalRNG); // do poprawy
    bool occupyTableInstantly = instantTableOccupation == 1;
    if(!waitingCustomers.empty()) {
        Customer* customer = waitingCustomers[0];
        if(customer->isWaitingToEnter()) {
            ChairPositionsAndDirections chairPositionsAndDirections = tablesManager->getFreeChairPositions(tableNumber);
            if(occupyTableInstantly) {
                tablesManager->occupyTableInstantly(tableNumber);
            }
            customer->setTableNumber(tableNumber);
            customer->setOccupyTableInstantly(occupyTableInstantly);
            customer->setTableNumberChairAndEnterChairPositions(scaleFactor, 
                                                                tableNumber, 
                                                                chairPositionsAndDirections.chairPositions, 
                                                                chairPositionsAndDirections.enterChairPositions);
            customer->setChairHorizontalDirection(chairPositionsAndDirections.chairHorizontalDirection);
            customer->setChairVerticalDirection(chairPositionsAndDirections.chairVerticalDirection);
            customer->changeToEnteredState();
            insideCustomers.push_back(customer);
            waitingCustomers.erase(waitingCustomers.begin());
        }
    }
}

void CharactersManager::moveInsideCustomerToLeaving(int index, TablesManager* tablesManager) {
    if(index >= 0 && index < insideCustomers.size()) {
        Customer* customer = insideCustomers[index];
        int tableNumber = customer->getTableNumber();
        Directions chairHorizontalDirection = customer->getChairHorizontalDirection();
        Directions chairVerticalDirection = customer->getChairVerticalDirection();
        tablesManager->freeChair(tableNumber, chairHorizontalDirection, chairVerticalDirection);
        if(customer->getOccupyTableInstantly()) {
            tablesManager->freeInstantlyOccupiedTable(tableNumber, tablesManager);
        }
        customer->changeToLeavingState();
        leavingCustomers.push_back(customer);
        insideCustomers.erase(insideCustomers.begin() + index);
    }
}

void CharactersManager::removeResigningCustomer(int index) {
    if(index >= 0 && index < resigningCustomers.size()) {
        delete resigningCustomers[index];
        resigningCustomers.erase(resigningCustomers.begin() + index);
    }
}

void CharactersManager::removeLeavingCustomer(int index) {
    if(index >= 0 && index < leavingCustomers.size()) {
        delete leavingCustomers[index];
        leavingCustomers.erase(leavingCustomers.begin() + index);
    }
}

Waiter* CharactersManager::getNearestWaiterToPositions(Waiter* nearestWaiter, 
                                                       Waiter* newWaiter, 
                                                       Positions positions) {
    if(nearestWaiter == nullptr) {
        return newWaiter;
    }
    float actualNearestWaiterXPos = nearestWaiter->getXPos();
    float actualNearestWaiterYPos = nearestWaiter->getYPos();
    float distanceToActualNearestWaiter = std::sqrt(std::pow(positions.xPos - actualNearestWaiterXPos, 2) 
                                                    + std::pow(positions.yPos - actualNearestWaiterYPos, 2));

    float newWaiterXPos = newWaiter->getXPos();
    float newWaiterYPos = newWaiter->getYPos();
    float distanceToNewWaiter = std::sqrt(std::pow(positions.xPos - newWaiterXPos, 2) 
                                          + std::pow(positions.yPos - newWaiterYPos, 2));

    if(distanceToNewWaiter < distanceToActualNearestWaiter) {
        return newWaiter;
    }

    return nearestWaiter;
}

void CharactersManager::getNearestWaiterToQueueHandling(int scaleFactor, Waiter* newWaiter) {
    Positions queueHandlingPositions{waitersQueueHandlingPositions.xPos * scaleFactor,
                                     waitersQueueHandlingPositions.yPos * scaleFactor};
    queueNearestWaiter = getNearestWaiterToPositions(queueNearestWaiter, 
                                                     newWaiter, 
                                                     queueHandlingPositions);
}

void CharactersManager::assignNearestWaiterToQueueHandling() {
    if(queueNearestWaiter != nullptr) {
        queueNearestWaiter->changeToQueueHandlingState();
    }
}

void CharactersManager::update(float deltaTime, int scaleFactor, float tileWidth, 
                               float tileHeight, TablesManager* tablesManager, 
                               PathFinder* pathFinder) {
    
    addCustomerTimer += deltaTime;
    if(addCustomerTimer > timeToAddCustomer && waitingCustomers.size() < 9) {
        addCustomerTimer = 0.0f;
        addWaitingCustomer(scaleFactor, tileWidth, tileHeight, moveXSpeed, moveYSpeed);
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
    
    if(waiters.size() >= 1) {
        queueNearestWaiter = waiters[0];
    }
    bool isFreeTables = tablesManager->isFreeTable();
    for(Waiter* waiter : waiters) {
        waiter->update(deltaTime, tileWidth, tileHeight, pathFinder);
        if(isFreeTables) {
            if(!queueNearestWaiter->getIsAssignedToTask() && 
               !queueNearestWaiter->getIsQueueHandling()) {
               getNearestWaiterToQueueHandling(scaleFactor, waiter);
            }
            
            int tableNumber = tablesManager->getFreeTableNumber();
            if(waiter->getIsQueueHandling() && tablesManager->isFreeChair(tableNumber)) {
                moveWaitingCustomerToInside(scaleFactor, tableNumber, tablesManager);
            }
        }
    }
    std::cout << "Nearest waiter" << queueNearestWaiter->getWaiterNumber() << std::endl; // do usunięcia
    if(isFreeTables) {
        if(!queueNearestWaiter->getIsAssignedToTask() && 
           !queueNearestWaiter->getIsQueueHandling()) {
            assignNearestWaiterToQueueHandling();
        }
    }

    for(int i = 0; i < waitingCustomers.size(); i++) {
        if(i == 0) {
            waitingCustomers[i]->updateIfWaiting(deltaTime, customersQueueStartingPositions.xPos * scaleFactor);
        }
        else {
            waitingCustomers[i]->updateIfWaiting(deltaTime, waitingCustomers[i - 1]->getXPos() + tileWidth);
        }
    }
    for(int i = resigningCustomers.size() - 1; i >= 0; i--) {
        resigningCustomers[i]->updateIfResigning(deltaTime);
        if(resigningCustomers[i]->getAssignedToRemoveStatus()) {
            removeResigningCustomer(i);
        }
    }
    for(int i = 0; i < insideCustomers.size(); i++) {
        insideCustomers[i]->updateIfEntered(deltaTime, scaleFactor, 
                                            tileWidth, tileHeight, 
                                            pathFinder);
        if(insideCustomers[i]->getLeaveRestaurantStatus()) {
            moveInsideCustomerToLeaving(i, tablesManager);
        }
    }
    for(int i = leavingCustomers.size() - 1; i >= 0; i--) {
        leavingCustomers[i]->updateIfLeaving(deltaTime);
        if(leavingCustomers[i]->getAssignedToRemoveStatus()) {
            removeLeavingCustomer(i);
        }
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
    for(Customer* insideCustomer : insideCustomers) {
        insideCustomer->render(window);
    }
    for(Customer* leavingCustomer : leavingCustomers) {
        leavingCustomer->render(window);
    }
}