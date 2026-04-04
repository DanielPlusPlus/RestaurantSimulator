#pragma once

#include "structures/CharactersTexturesPaths.hpp"
#include "enums/DirectionsEnum.hpp"
#include "Chef.hpp"
#include "Waiter.hpp"
#include "Customer.hpp"

#include <SFML/Graphics.hpp>


class CharactersManager {
private:
    const CharactersTexturesPaths customersTexturesPaths[2] = {
        CharactersTexturesPaths{"assets/characters/customer_1/customer1_idle.png", 
                                "assets/characters/customer_1/customer1_run.png", 
                                "assets/characters/customer_1/customer1_sit.png"},
        CharactersTexturesPaths{"assets/characters/customer_2/customer2_idle.png", 
                                "assets/characters/customer_2/customer2_run.png", 
                                "assets/characters/customer_2/customer2_sit.png"}
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
        Positions{38.0f, 24.0f},
        Positions{38.0f, 24.0f},
        Positions{38.0f, 24.0f}
    };
    const Positions customersStartPosition{38.0f, 24.0f};

    std::vector<Chef*> chefs;
    std::vector<Waiter*> waiters;
    std::queue<Customer*> waitingCustomers;
    std::vector<Customer*> insideCustomers;
    void addChefs(int scaleFactor, float tileWidth, float tileHeight, float moveXSpeed, 
                  float moveYSpeed, int chefsNumber, DishesManager* dishesManager);
    void addWaiters(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, int waitersNumber);
    void addCustomer(int scaleFactor, float tileWidth, float tileHeight, float wallWidth, 
                     CharactersTexturesPaths texturesPaths);
    void removeCustomer();
public:
    CharactersManager(int scaleFactor, float tileWidth, float tileHeight, 
                      int chefsNumber, int waitersNumber, DishesManager* dishesManager);
    void update(float deltaTime, int scaleFactor);
    void render(sf::RenderWindow* window);
};