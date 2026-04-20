#include "items/DishesManager.hpp"

#include <random>


DishesManager::DishesManager(int scaleFactor) {
    readyDishesPositions.xPos *= scaleFactor;
    readyDishesPositions.yPos *= scaleFactor;
}

void DishesManager::addDish(int scaleFactor, int tableNumber) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> dist(2, 5);
    Dish* newDish = new Dish(scaleFactor, dishesTexturesPaths[dist(globalRNG) % 
                             (sizeof(dishesTexturesPaths) / sizeof(std::string))], 
                             readyDishesPositions, tableNumber);
    readyDishes.push(newDish);
}

Positions DishesManager::getReadyDishesPositions() {
    return readyDishesPositions;
}

void DishesManager::moveReadyDishToMoving() {
    if(!readyDishes.empty()) {
        movingToTableDish = readyDishes.front();
        readyDishes.pop();
    }
}

void DishesManager::moveMovingDishToDishesOnTables(Positions newDishPositions) {
    movingToTableDish->changePositions(newDishPositions);
    dishesOnTables.push_back(movingToTableDish);
    movingToTableDish = nullptr;
}

void DishesManager::removeDishesOnTable(int tableNumber) {
    for(Dish* dish : dishesOnTables) {
        if(dish->getTableNumber() == tableNumber) {
            dishesOnTables.erase(std::remove(dishesOnTables.begin(), 
                                 dishesOnTables.end(), dish), 
                                 dishesOnTables.end());
            delete dish;
        }
    }
}

void DishesManager::render(sf::RenderWindow* window) {
    if(!readyDishes.empty()) {
        readyDishes.front()->render(window);
    }
    for(Dish* dish : dishesOnTables) {
        dish->render(window);
    }
}