#pragma once

#include "structures/Positions.hpp"
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
    std::queue<Dish*> readyDishes;
    std::vector<Dish*> movingToTablesDishes;
    std::vector<Dish*> dishesOnTables;
    bool isReadyDishWaitingForWaiter = false;
public:
    DishesManager(int scaleFactor);
    ~DishesManager();
    void addDish(int scaleFactor, int tableNumber);
    Positions getReadyDishesPositions();
    void moveReadyDishToMoving();
    void moveMovingDishToDishesOnTables(int tableNumber, Positions newDishPositions);
    void removeAllDishesOnTable(int tableNumber, int* dishesOnTableNumber);
    void render(sf::RenderWindow* window);
    void renderReadyDish(sf::RenderWindow* window);
    bool isReadyDishes() {
        return !readyDishes.empty();
    }
    int getReadyDishTableNumber();
    bool isDishesOnTables() {
        return !dishesOnTables.empty();
    }
    void setReadyDishWaitingForWaiter(bool value) {
        isReadyDishWaitingForWaiter = value;
    }
    bool getReadyDishWaitingForWaiterStatus() {
        return isReadyDishWaitingForWaiter;
    }
    std::vector<int> getDishesOnTablesNumbers();
    std::vector<Dish*>& getDishesOnTables() {
        return dishesOnTables;
    }
};