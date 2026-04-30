#include "items/DishesManager.hpp"

#include <algorithm>
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
        setReadyDishWaitingForWaiter(false);
        movingToTablesDishes.push_back(readyDishes.front());
        readyDishes.front()->getTableNumber();
        readyDishes.pop();
    }
}

void DishesManager::moveMovingDishToDishesOnTables(int tableNumber, Positions newDishPositions) {
    for(auto it = movingToTablesDishes.begin(); it != movingToTablesDishes.end(); it++) {
        Dish* dish = *it;
        if(dish->getTableNumber() == tableNumber) {
            dish->changePositions(newDishPositions);
            dishesOnTables.push_back(dish);
            movingToTablesDishes.erase(it);
            return;
        }
    }
}

void DishesManager::removeAllDishesOnTable(int tableNumber, int* dishesOnTableNumber) {
    *dishesOnTableNumber = 0;
    auto newEnd = std::remove_if(dishesOnTables.begin(), dishesOnTables.end(),
                                 [tableNumber, dishesOnTableNumber](Dish* dish) {
                                     if(dish->getTableNumber() == tableNumber) {
                                         delete dish;
                                         (*dishesOnTableNumber)++;
                                         return true;
                                     }
                                     return false;
                                 });
    dishesOnTables.erase(newEnd, dishesOnTables.end());
}

void DishesManager::render(sf::RenderWindow* window) {
    if(!readyDishes.empty()) {
        readyDishes.front()->render(window);
    }
    for(Dish* dish : dishesOnTables) {
        dish->render(window);
    }
}

void DishesManager::renderReadyDish(sf::RenderWindow* window) {
    if(!readyDishes.empty()) {
        readyDishes.front()->render(window);
    }
}

int DishesManager::getReadyDishTableNumber() {
    if(!readyDishes.empty()) {
        return readyDishes.front()->getTableNumber();
    }
    return -1;
}

std::vector<int> DishesManager::getDishesOnTablesNumbers() {
    std::vector<int> dishesOnTablesNumbers;
    for(Dish* dish : dishesOnTables) {
        dishesOnTablesNumbers.push_back(dish->getTableNumber());
    }
    return dishesOnTablesNumbers;
}