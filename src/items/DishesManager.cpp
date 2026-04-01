#include "items/DishesManager.hpp"

#include <ctime>
#include <cstdlib>

DishesManager::DishesManager(float tileWidth, float tileHeight, float wallWidth) {
    readyDishesXPos = wallWidth + tileWidth * 8.0f;
    readyDishesYPos = tileHeight * 2.5f;
}

void DishesManager::addDish(int scaleFactor, int tableNumber) {
    srand(time(NULL));
    Dish* newDish = new Dish(scaleFactor, dishesTextures[rand() % (sizeof(dishesTextures) / sizeof(std::string))], 
                             readyDishesXPos, readyDishesYPos, tableNumber);
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