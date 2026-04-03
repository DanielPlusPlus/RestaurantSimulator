#pragma once

#include "structures/Positions.hpp"
#include "Dish.hpp"

#include <queue>
#include <SFML/Graphics.hpp>


class DishesManager {
private:
    Positions readyDishesPositions{134.0f, 40.0f};
    const std::string dishesTexturesPaths[5] = {
        "assets/items/dishes/soup.png",
        "assets/items/dishes/soup_2.png",
        "assets/items/dishes/cake.png",
        "assets/items/dishes/cake_2.png",
        "assets/items/dishes/pizza.png"
    };
    std::queue<Dish*> readyDishes;
public:
    DishesManager(int scaleFactor);
    void addDish(int scaleFactor, int tableNumber);
    void removeDish();
    void render(sf::RenderWindow* window);
};