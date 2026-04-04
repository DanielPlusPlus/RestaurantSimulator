#include "items/DishesManager.hpp"

#include <random>

DishesManager::DishesManager(int scaleFactor) {
    readyDishesPositions.xPos *= scaleFactor;
    readyDishesPositions.yPos *= scaleFactor;
}

void DishesManager::addDish(int scaleFactor, int tableNumber) {
    extern std::mt19937 globalRNG;
    std::uniform_int_distribution<int> dist(2, 5);
    Dish* newDish = new Dish(scaleFactor, dishesTexturesPaths[dist(globalRNG) % (sizeof(dishesTexturesPaths) / sizeof(std::string))], 
                             readyDishesPositions, tableNumber);
    readyDishes.push(newDish);
}

Positions DishesManager::getReadyDishesPositions() {
    return readyDishesPositions;
}

void DishesManager::removeDish() {
    if(!readyDishes.empty()) {
        delete readyDishes.front();
        readyDishes.pop();
    }
}

void DishesManager::render(sf::RenderWindow* window) {
    if(!readyDishes.empty()) {
        readyDishes.front()->render(window);
    }
}