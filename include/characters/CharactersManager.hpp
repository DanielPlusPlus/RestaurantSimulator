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


class Level;

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
    // const Positions waitersStartPositions[3] = {
    //     Positions{143.0f, 168.0f},
    //     Positions{151.0f, 40.0f},
    //     Positions{70.0f, 72.0f}
    // };
    const Positions waitersStartPositions[3] = {
        Positions{143.0f, 168.0f},
        Positions{151.0f, 40.0f},
        Positions{70.0f, 72.0f}
    };
    const Positions customersStartPositions{302.0f, 178.0f};
    // y - 162, x - 131 lewa, 171 prawa, srodek 131 + (171 - 131) / 2 = 151
    const Positions waiterQueueHandlingPositions{143.0f, 168.0f};
    const Positions waiterDishPickupPositions{151.0f, 40.0f};
    const Positions waiterDishDropoffPositions{70.0f, 72.0f};
    const Positions customersQueueStartingPositions{155.0f, 178.0f};
    
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
    void addChefs(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
                  float moveYSpeed, int chefsNumber, DishesManager* dishesManager);
    void addWaiters(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
                    float moveYSpeed, int waitersNumber);
    void addCustomer(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, float moveYSpeed);
    void moveWaitingCustomerToResignation();
    void removeResigningCustomer(int index);
public:
    CharactersManager(int scaleFactor, float tileWidth, float tileHeight, 
                      int chefsNumber, int waitersNumber, DishesManager* dishesManager);
    void update(float deltaTime, int scaleFactor, float tileWidth, float tileHeight, Level* level);
    void renderChefs(sf::RenderWindow* window);
    void renderWaitersAndCustomers(sf::RenderWindow* window);
};