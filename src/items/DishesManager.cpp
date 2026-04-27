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
        movingToTablesDishes.push_back(readyDishes.front());
        readyDishes.front()->getTableNumber();
        readyDishes.pop();
    }
}

void DishesManager::moveMovingDishToDishesOnTables(int tableNumber, Positions newDishPositions) {
    for(Dish* dish : movingToTablesDishes) {
        if(dish->getTableNumber() == tableNumber) {
            dish->changePositions(newDishPositions);
            dishesOnTables.push_back(dish);
            movingToTablesDishes.erase(std::remove(movingToTablesDishes.begin(), 
                                         movingToTablesDishes.end(), dish), 
                                         movingToTablesDishes.end());
            return;
        }
    }
}

void DishesManager::removeAllDishesOnTable(int tableNumber) {
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