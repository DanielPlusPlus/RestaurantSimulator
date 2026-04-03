#include "items/DishesManager.hpp"

#include <ctime>
#include <cstdlib>

DishesManager::DishesManager(int scaleFactor) {
    readyDishesPositions.xPos *= scaleFactor;
    readyDishesPositions.yPos *= scaleFactor;
}

void DishesManager::addDish(int scaleFactor, int tableNumber) {
    srand(time(NULL));
    Dish* newDish = new Dish(scaleFactor, dishesTexturesPaths[rand() % (sizeof(dishesTexturesPaths) / sizeof(std::string))], 
                             readyDishesPositions, tableNumber);
    readyDishes.push(newDish);
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