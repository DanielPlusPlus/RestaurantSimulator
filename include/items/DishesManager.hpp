#pragma once

#include "structures/Positions.hpp"
#include "structures/DishesPositionsForFourChairsTables.hpp"
#include "Dish.hpp"

#include <queue>
#include <SFML/Graphics.hpp>


class DishesManager {
private:
    const std::string dishesTexturesPaths[5] = {
        "assets/items/dishes/soup.png",
        "assets/items/dishes/soup_2.png",
        "assets/items/dishes/cake.png",
        "assets/items/dishes/cake_2.png",
        "assets/items/dishes/pizza.png"
    };
    Positions readyDishesPositions{134.0f, 47.0f};
    Positions dishesServingPositionsForTwoChairsTables[8] = {
        Positions{70.5f, 142.0f},
        Positions{194.0f, 142.0f},
        Positions{22.0f, 142.0f},
        Positions{22.0f, 113.0f},
        Positions{22.0f, 84.0f},
        Positions{119.0f, 84.0f},
        Positions{175.0f, 21.0f},
        Positions{254.0f, 21.0f}
    };
    DishesPositionsForFourChairsTables dishesServingPositionsForFourChairsTables[3] = {
        DishesPositionsForFourChairsTables{244.0f, 147.0f, 262.0f, 147.0f, 244.0f, 132.0f, 262.0f, 132.0f},
        DishesPositionsForFourChairsTables{244.0f, 106.0f, 262.0f, 106.0f, 244.0f, 91.0f, 262.0f, 91.0f},
        DishesPositionsForFourChairsTables{244.0f, 65.0f, 262.0f, 65.0f, 244.0f, 50.0f, 262.0f, 50.0f}
    };
    std::queue<Dish*> readyDishes;
public:
    DishesManager(int scaleFactor);
    void addDish(int scaleFactor, int tableNumber);
    void removeDish();
    Positions getReadyDishesPositions();
    void render(sf::RenderWindow* window);
};