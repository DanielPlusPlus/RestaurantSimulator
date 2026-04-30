#pragma once

#include "structures/CharactersTexturesPaths.hpp"
#include "enums/DirectionsEnum.hpp"
#include "Chef.hpp"
#include "Waiter.hpp"
#include "Customer.hpp"

#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>
#include <vector>


class TablesManager;;
class PathFinder;

class CharactersManager {
private:
    const CharactersTexturesPaths customersTexturesPaths[2] = {
        CharactersTexturesPaths{"assets/characters/customer_1/customer_1_idle.png", 
                                "assets/characters/customer_1/customer_1_run.png", 
                                "assets/characters/customer_1/customer_1_sit.png"},
        CharactersTexturesPaths{"assets/characters/customer_2/customer_2_idle.png", 
                                "assets/characters/customer_2/customer_2_run.png", 
                                "assets/characters/customer_2/customer_2_sit.png"}
    };
    const Positions chefsStartPositions[3] = {
        Positions{102.0f, 40.0f},
        Positions{38.0f, 24.0f},
        Positions{38.0f, 40.0f}
    };
    const enum Directions chefsStartDirections[3] = {
        Directions::DOWN,
        Directions::UP,
        Directions::DOWN
    };
    const Positions waitersStartPositions[3] = {
        Positions{143.0f, 168.0f},
        Positions{151.0f, 40.0f},
        Positions{70.0f, 72.0f}
    };
    const Positions customersStartPositions{302.0f, 178.0f};
    const Positions waitersQueueHandlingPositions{143.0f, 168.0f};
    const Positions waitersDishPickupPositions{151.0f, 40.0f};
    const Positions waitersDishDropoffPositions{70.0f, 72.0f};
    const Positions customersQueueStartingPositions{155.0f, 178.0f};
    const Positions customersEnterRestaurantPositions{155.0f, 152.0f};
    const Positions customersExitRestaurantPositions{131.0f, 152.0f};

    int totalCustomersNumberCounter = 0;
    int resigningCustomersNumberCounter = 0;
    int insideCustomersNumberCounter = 0;
    int leavingCustomersNumberCounter = 0;
    int orderedDishesNumberCounter = 0;
    int preparedDishesNumberCounter = 0;
    int servedDishesNumberCounter = 0;
    int eatenDishesNumberCounter = 0;
    int droppedDishesNumberCounter = 0;

    std::uniform_real_distribution<float> timeToAddCustomerDist;
    std::uniform_real_distribution<float> timeToRemoveCustomerDist;

    float moveXSpeed = 0.0f;
    float moveYSpeed = 0.0f;
    float timeToAddCustomer = 0.0f;
    float timeToRemoveWaitingCustomer = 0.0f;
    float addCustomerTimer = 0.0f;
    float removeWatingCustomerTimer = 0.0f;

    std::vector<Chef*> chefs;
    std::vector<Waiter*> waiters;
    std::vector<Customer*> waitingCustomers;
    std::vector<Customer*> insideCustomers;
    std::vector<Customer*> resigningCustomers;
    std::vector<Customer*> leavingCustomers;

    Waiter* queueNearestWaiter = nullptr;

    void addChefs(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
                  float moveYSpeed, int chefsNumber, DishesManager* dishesManager);
    void addWaiters(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
                    float moveYSpeed, int waitersNumber, DishesManager* dishesManager);
    void addWaitingCustomer(int scaleFactor, float tileWidth, float tileHeight, 
                            float moveXSpeed, float moveYSpeed);
    void moveWaitingCustomerToResignation();
    void moveWaitingCustomerToInside(int scaleFactor, int tableNumber, 
                                     TablesManager* tablesManager);
    void removeResigningCustomer(int index);
    void removeLeavingCustomer(int index);
    void moveInsideCustomerToLeaving(int index, TablesManager* tablesManager);
    Waiter* getNearestWaiterToPositions(Waiter* newWaiter, 
                                        Waiter* nearestWaiter, 
                                        Positions positions);
    void getNearestWaiterToQueueHandling(int scaleFactor, Waiter* newWaiter);
    bool checkIsWaiterInQueueHandling();
    void assignNearestWaiterToQueueHandling();
    void assignWaitersToTablesHandling(int scaleFactor, TablesManager* tablesManager);
    void assignChefsToCooking(int tableNumber);
    void assignWaitersToDishPickup(int scaleFactor, 
                                   DishesManager* dishesManager, 
                                   TablesManager* tablesManager);
    void assignCustomersToEating(DishesManager* dishesManager);
    void assignWaitersToDishDropoff(int scaleFactor, 
                                    TablesManager* tablesManager, 
                                    DishesManager* dishesManager);
public:
    CharactersManager(int scaleFactor, float tileWidth, float tileHeight, 
                      int chefsNumber, int waitersNumber, DishesManager* dishesManager);
    void update(float deltaTime, int scaleFactor, 
                float tileWidth, float tileHeight, 
                DishesManager* dishesManager, 
                TablesManager* tablesManager, 
                PathFinder* pathFinder);
    void renderChefs(sf::RenderWindow* window);
    void renderWaitersAndInsideCustomers(sf::RenderWindow* window);
    void renderWaitingResigningInsideLeavingCustomers(sf::RenderWindow* window);
    std::vector<Character*> getWaitersAndInsideCustomers();
    void getStatistics(int* totalCustomersNumberPtr, int* resigningCustomersNumberPtr, 
                       int* insideCustomersNumberPtr, int* leavingCustomersNumberPtr, 
                       int* orderedDishesNumberPtr, int* preparedDishesNumberPtr, 
                       int* servedDishesNumberPtr, int* eatenDishesNumberPtr, 
                       int* droppedDishesNumberPtr);
};