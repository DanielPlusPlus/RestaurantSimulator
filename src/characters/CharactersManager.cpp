#include "characters/CharactersManager.hpp"
#include "characters/Chef.hpp"
#include "characters/Waiter.hpp"
#include "characters/Customer.hpp"
#include "interiors/TablesManager.hpp"

#include <random>
#include <algorithm>
#include <unordered_map>
#include <iostream>


CharactersManager::CharactersManager(int scaleFactor, float tileWidth, float tileHeight, int chefsNumber, 
                                     int waitersNumber, DishesManager* dishesManager
                                     ) : timeToAddCustomerDist(10.0f, 20.0f),
                                         timeToRemoveCustomerDist(20.0f, 40.0f) {
    moveXSpeed = tileWidth;
    moveYSpeed = tileHeight;

    extern std::mt19937 globalRNG;
    timeToRemoveWaitingCustomer = timeToRemoveCustomerDist(globalRNG);
    
    addChefs(scaleFactor, tileWidth, tileHeight, 
             moveXSpeed, moveYSpeed, chefsNumber, 
             dishesManager);
    addWaiters(scaleFactor, tileWidth, tileHeight, 
               moveXSpeed, moveYSpeed, waitersNumber, 
               dishesManager);
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
                                   float moveXSpeed, float moveYSpeed, int waitersNumber,
                                   DishesManager* dishesManager) {
    for(int i = 0; i < waitersNumber; i++) {
        Waiter* newWaiter = new Waiter(scaleFactor, moveXSpeed, moveYSpeed, i + 1, 
                                       waitersStartPositions[i], waitersQueueHandlingPositions, 
                                       waitersDishPickupPositions, waitersDishDropoffPositions,
                                       dishesManager);
        waiters.push_back(newWaiter);
    }
}

void CharactersManager::addWaitingCustomer(int scaleFactor, float tileWidth, float tileHeight, 
                                           float moveXSpeed, float moveYSpeed) {
    totalCustomersNumberCounter++;
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> customerTextureDist(0, 1);
    Customer* newCustomer = new Customer(scaleFactor, customersTexturesPaths[customerTextureDist(globalRNG)], 
                                         tileWidth, tileHeight, moveXSpeed, moveYSpeed, 
                                         totalCustomersNumberCounter, 
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
        resigningCustomersNumberCounter++;
        waitingCustomers.erase(waitingCustomers.begin() + index);
    }
    timeToRemoveWaitingCustomer = timeToRemoveCustomerDist(globalRNG);
}

void CharactersManager::moveWaitingCustomerToInside(int scaleFactor, int tableNumber, 
                                                    TablesManager* tablesManager) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> instantTableOccupationDist(1, 4);
    int instantTableOccupation = instantTableOccupationDist(globalRNG);
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
            customer->setIsLastCustomerOnTable(tablesManager->checkIsLastCustomerOnTable(tableNumber));
            customer->setTableNumberChairAndEnterChairPositions(scaleFactor, 
                                                                tableNumber, 
                                                                chairPositionsAndDirections.chairPositions, 
                                                                chairPositionsAndDirections.enterChairPositions);
            customer->setChairHorizontalDirection(chairPositionsAndDirections.chairHorizontalDirection);
            customer->setChairVerticalDirection(chairPositionsAndDirections.chairVerticalDirection);
            customer->changeToEnteredState();
            insideCustomers.push_back(customer);
            insideCustomersNumberCounter++;
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
            tablesManager->freeInstantlyOccupiedTable(tableNumber);
            tablesManager->setWaitingToDishesTaken(tableNumber);
        }
        customer->changeToLeavingState();
        leavingCustomers.push_back(customer);
        leavingCustomersNumberCounter++;
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

bool CharactersManager::checkIsWaiterInQueueHandling() {
    for(Waiter* waiter : waiters) {
        if(waiter->getIsQueueHandling() || 
           waiter->getIsSelectedToQueueHandling()) {
            return true;
        }
    }
    return false;
}

void CharactersManager::assignNearestWaiterToQueueHandling() {
    if(queueNearestWaiter != nullptr) {
        queueNearestWaiter->changeToQueueHandlingState();
    }
}

void CharactersManager::assignWaitersToTablesHandling(int scaleFactor, TablesManager* tablesManager) {
    std::vector<int> waitingToHandlingTablesNumbers = tablesManager->getWaitingToHandlingTablesNumbers();
    for(int tableNumber : waitingToHandlingTablesNumbers) {
        Positions tableHandlingPositions = tablesManager->getTableHandlingPositions(tableNumber);
        Waiter* tableNearestWaiter = nullptr;
        for(Waiter* waiter : waiters) {
            if(!waiter->getIsAssignedToTask()) {
                tableNearestWaiter = getNearestWaiterToPositions(tableNearestWaiter, 
                                                                 waiter, 
                                                                 tableHandlingPositions);
            }
        }
        if(tableNearestWaiter != nullptr) {
            std::cout << "Assigning waiter " << tableNearestWaiter->getWaiterNumber() << " to handle table " << tableNumber << std::endl;
            Directions tableHandlingDirection = tablesManager->getTableHandlingDirection(tableNumber);
            tableNearestWaiter->setTableNumberPositionsAndDirection(scaleFactor, tableNumber, 
                                                                   tableHandlingPositions, 
                                                                   tableHandlingDirection);
            tableNearestWaiter->changeToTableHandlingState();
            tableNearestWaiter->setAssignedToTask(true);
            tablesManager->resetWaitingToHandling(tableNumber);
        }
    }
}

void CharactersManager::assignChefsToCooking(int tableNumber) {
    if(chefs.empty()) {
        return;
    }

    Chef* chefWithMinDishesNumber = chefs[0];
    int minDishesToCookForNumber = chefWithMinDishesNumber->getDishesToCookForNumber();

    for(Chef* chef : chefs) {
        int dishesToCookForNumber = chef->getDishesToCookForNumber();
        if(dishesToCookForNumber < minDishesToCookForNumber) {
            chefWithMinDishesNumber = chef;
            minDishesToCookForNumber = dishesToCookForNumber;
        }
    }

    chefWithMinDishesNumber->addTableToCookFor(tableNumber);
}

void CharactersManager::assignWaitersToDishPickup(int scaleFactor, 
                                                  DishesManager* dishesManager,
                                                  TablesManager* tablesManager) {
    int readyDishTableNumber = dishesManager->getReadyDishTableNumber();
    Positions tableHandlingPositions = tablesManager->getTableHandlingPositions(readyDishTableNumber);
    Positions dishPickupPositions = {waitersDishPickupPositions.xPos * scaleFactor, 
                                     waitersDishPickupPositions.yPos * scaleFactor};
    Waiter* tableNearestWaiter = nullptr;
    for(Waiter* waiter : waiters) {
        if(!waiter->getIsAssignedToTask()) {
            tableNearestWaiter = getNearestWaiterToPositions(tableNearestWaiter, 
                                                              waiter, 
                                                              dishPickupPositions);
            }
    }
    if(tableNearestWaiter != nullptr) {
        std::cout << "Assigning waiter " << tableNearestWaiter->getWaiterNumber() << " to pickup dish and deliver to table " << readyDishTableNumber << std::endl;
        dishesManager->setReadyDishWaitingForWaiter(true);
        Directions tableHandlingDirection = tablesManager->getTableHandlingDirection(readyDishTableNumber);
        tableNearestWaiter->setTableNumberPositionsAndDirection(scaleFactor, readyDishTableNumber, 
                                                                tableHandlingPositions, 
                                                                tableHandlingDirection);
        tableNearestWaiter->changeToDishPickupState();
        tableNearestWaiter->setAssignedToTask(true);
    }
}

void CharactersManager::assignCustomersToEating(DishesManager* dishesManager) {
    std::vector<int> dishesOnTablesNumbers = dishesManager->getDishesOnTablesNumbers();
    std::unordered_map<int, int> tableOccupancyCount;
    for(int tableNumber : dishesOnTablesNumbers) {
        tableOccupancyCount[tableNumber]++;
    }

    for(int tableNumber : dishesOnTablesNumbers) {
        extern std::mt19937 globalRNG;
        std::uniform_int_distribution<int> instantTableOccupationDist(5, 10);
        float eatingTime = float(instantTableOccupationDist(globalRNG));

        int customersAtTable = 0;
        for (Customer* customer : insideCustomers) {
            if(customer->getTableNumber() == tableNumber && customer->isSitting()) {
                customersAtTable++;
            }
        }

        if(customersAtTable == tableOccupancyCount[tableNumber]) {
            for(Customer* customer : insideCustomers) {
                if(customer->getTableNumber() == tableNumber && customer->isSitting()) {
                    std::cout << "Assigning customer " << customer->getCustomerNumber() << " to eat at table " << tableNumber << std::endl;
                    customer->setEatingTime(eatingTime);
                    customer->changeToEatingState();
                }
            }
        }
    }
}

void CharactersManager::assignWaitersToDishDropoff(int scaleFactor, 
                                                   TablesManager* tablesManager, 
                                                   DishesManager* dishesManager) {
    std::vector<int> waitingToDishesTakenTablesNumbers = tablesManager->getWaitingToDishesTakenTablesNumbers();
    for(int tableNumber : waitingToDishesTakenTablesNumbers) {
        Positions tableHandlingPositions = tablesManager->getTableHandlingPositions(tableNumber);
        Waiter* tableNearestWaiter = nullptr;
        for(Waiter* waiter : waiters) {
            if(!waiter->getIsAssignedToTask()) {
                tableNearestWaiter = getNearestWaiterToPositions(tableNearestWaiter, 
                                                                 waiter, 
                                                                 tableHandlingPositions);
            }
        }
        if(tableNearestWaiter != nullptr) {
            std::cout << "Assigning waiter " << tableNearestWaiter->getWaiterNumber() << " to dropoff dish to table " << tableNumber << std::endl;
            Directions tableHandlingDirection = tablesManager->getTableHandlingDirection(tableNumber);
            tableNearestWaiter->setTableNumberPositionsAndDirection(scaleFactor, tableNumber, 
                                                                    tableHandlingPositions, 
                                                                    tableHandlingDirection);
            tableNearestWaiter->changeToDishDropoffState();
            tableNearestWaiter->setAssignedToTask(true);
            tablesManager->resetWaitingToDishesTaken(tableNumber);
        }
    }
}

void CharactersManager::update(float deltaTime, int scaleFactor, 
                               float tileWidth, float tileHeight, 
                               DishesManager* dishesManager, 
                               TablesManager* tablesManager, 
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
    
    for(Chef* chef : chefs) {
        int addedDishesNumber = 0;
        chef->update(deltaTime, scaleFactor, &addedDishesNumber);
        preparedDishesNumberCounter += addedDishesNumber;
    }
    
    queueNearestWaiter = nullptr;
    bool isFreeTable = tablesManager->isFreeTable();
    bool isTablesWaitingToHandling = tablesManager->isTablesWaitingToHandling();
    bool isWaiterInQueueHandling = checkIsWaiterInQueueHandling();
    bool isReadyDishes = dishesManager->isReadyDishes();
    bool isReadyDishWaitingForWaiter = dishesManager->getReadyDishWaitingForWaiterStatus();
    bool isWaitingTablesToDishTaken = tablesManager->isTablesWaitingToDishesTaken();
    for(Waiter* waiter : waiters) {
        waiter->update(deltaTime, tileWidth, tileHeight, pathFinder);

        if(isFreeTable) {
            if(!waiter->getIsAssignedToTask() && !isWaiterInQueueHandling) {
               getNearestWaiterToQueueHandling(scaleFactor, waiter);
            }
            
            int tableNumber = tablesManager->getFreeTableNumber();
            if(waiter->getIsQueueHandling() && tablesManager->isFreeChair(tableNumber)) {
                moveWaitingCustomerToInside(scaleFactor, tableNumber, tablesManager);
            }
        }

        if(waiter->getIsNewOrder()) {
            int dishesNumber = tablesManager->getOccupiedChairsNumber(waiter->getTableNumber());
            for(int i = 0; i < dishesNumber; i++) {
                assignChefsToCooking(waiter->getTableNumber());
            }
            waiter->setNewOrder(false);
            orderedDishesNumberCounter += dishesNumber;
        }
        
        if(waiter->getIsDishToPutdown()) {
            int tableNumber = waiter->getTableNumber();
            Positions dishesPositions = tablesManager->getDishesPositions(tableNumber);
            Positions scaleDishesPositions = {dishesPositions.xPos * scaleFactor, 
                                              dishesPositions.yPos * scaleFactor};
            dishesManager->moveMovingDishToDishesOnTables(tableNumber, 
                                                          scaleDishesPositions);
            servedDishesNumberCounter++;
            waiter->setIsDishToPutdown(false);
        }
        if(waiter->getIsDishesToDropoff()) {
            int tableNumber = waiter->getTableNumber();
            int dishesOnTableNumber = 0;
            dishesManager->removeAllDishesOnTable(tableNumber, &dishesOnTableNumber);
            droppedDishesNumberCounter += dishesOnTableNumber;
            waiter->setIsDishesToDropoff(false);
        }
    }

    if(isFreeTable && queueNearestWaiter != nullptr) {
        if(!queueNearestWaiter->getIsAssignedToTask() && !isWaiterInQueueHandling) {
            assignNearestWaiterToQueueHandling();
            queueNearestWaiter->setAssignedToTask(true);
        }
    }

    if(isTablesWaitingToHandling) {
        assignWaitersToTablesHandling(scaleFactor, tablesManager);
    }

    if(isReadyDishes && !isReadyDishWaitingForWaiter) {
        assignWaitersToDishPickup(scaleFactor, dishesManager, tablesManager);
    }

    if(isWaitingTablesToDishTaken) {
        assignWaitersToDishDropoff(scaleFactor, tablesManager, dishesManager);
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
                                            pathFinder, 
                                            &eatenDishesNumberCounter);
        if(insideCustomers[i]->isWaitingToSit()) {
            int tableNumber = insideCustomers[i]->getTableNumber();
            if(tablesManager->getTableOccupiedStatus(tableNumber) &&
               insideCustomers[i]->getIsLastCustomerOnTable()) {
                tablesManager->setWaitingToHandling(tableNumber);
                std::cout << "Table " << tableNumber << " is waiting to be handled" << std::endl;
            }
            insideCustomers[i]->changeToSittingState();
        }
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

    bool isDishesOnTables = dishesManager->isDishesOnTables();
    if(isDishesOnTables) {
        assignCustomersToEating(dishesManager);
    }
}

void CharactersManager::renderChefs(sf::RenderWindow* window) {
    for(Chef* chef : chefs) {
        chef->render(window);
    }
}

void CharactersManager::renderWaitersAndInsideCustomers(sf::RenderWindow* window) {
    for(Waiter* waiter : waiters) {
        waiter->render(window);
    }
    for(Customer* insideCustomer : insideCustomers) {
        insideCustomer->render(window);
    }
}

void CharactersManager::renderWaitingResigningInsideLeavingCustomers(sf::RenderWindow* window) {
    for(Customer* waitingCustomer : waitingCustomers) {
        waitingCustomer->render(window);
    }
    for(Customer* resigningCustomer : resigningCustomers) {
        resigningCustomer->render(window);
    }
    for(Customer* leavingCustomer : leavingCustomers) {
        leavingCustomer->render(window);
    }
}

std::vector<Character*> CharactersManager::getWaitersAndInsideCustomers() {
    std::vector<Character*> characters;
    characters.reserve(waiters.size() + insideCustomers.size());
    for(Waiter* waiter : waiters) {
        characters.push_back(waiter);
    }
    for(Customer* insideCustomer : insideCustomers) {
        characters.push_back(insideCustomer);
    }
    return characters;
}

void CharactersManager::getStatistics(int* totalCustomersNumberPtr, int* resigningCustomersNumberPtr, 
                                      int* insideCustomersNumberPtr, int* leavingCustomersNumberPtr, 
                                      int* orderedDishesNumberPtr, int* preparedDishesNumberPtr, 
                                      int* servedDishesNumberPtr, int* eatenDishesNumberPtr, 
                                      int* droppedDishesNumberPtr) {
    *totalCustomersNumberPtr = totalCustomersNumberCounter;
    *resigningCustomersNumberPtr = resigningCustomersNumberCounter;
    *insideCustomersNumberPtr = insideCustomersNumberCounter;
    *leavingCustomersNumberPtr = leavingCustomersNumberCounter;
    *orderedDishesNumberPtr = orderedDishesNumberCounter;
    *preparedDishesNumberPtr = preparedDishesNumberCounter;
    *servedDishesNumberPtr = servedDishesNumberCounter;
    *eatenDishesNumberPtr = eatenDishesNumberCounter;
    *droppedDishesNumberPtr = droppedDishesNumberCounter;
}