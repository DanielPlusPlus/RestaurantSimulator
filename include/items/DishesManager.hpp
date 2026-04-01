#pragma once

#include "Dish.hpp"

#include <queue>
#include <SFML/Graphics.hpp>


class DishesManager {
private:
    float readyDishesXPos = 0.0f;
    float readyDishesYPos = 0.0f;
    const std::string dishesTexturesPaths[5] = {
        "assets/items/dishes/soup.png",
        "assets/items/dishes/soup_2.png",
        "assets/items/dishes/cake.png",
        "assets/items/dishes/cake_2.png",
        "assets/items/dishes/pizza.png"
    };
    std::queue<Dish*> readyDishes;
public:
    DishesManager(float tileWidth, float tileHeight, float wallWidth);
    void addDish(int scaleFactor, int tableNumber);
    void removeDish();
    void render(sf::RenderWindow* window);
};