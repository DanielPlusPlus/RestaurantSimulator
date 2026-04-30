#pragma once

#include "scenes/Scene.hpp"
#include "enums/ScenesEnum.hpp"

#include <SFML/Graphics.hpp>


class Game {
private:
    int width = 302;
    int height = 234;
    enum ScenesEnum currentSceneName = ScenesEnum::MAIN_MENU;
    enum ScenesEnum newSceneName = ScenesEnum::MAIN_MENU;
    sf::RenderWindow* window;
    Scene* currentScene;

    int scaleFactor = 1;
    int chefsNumber = 1;
    int waitersNumber = 1;
    int twoChairsTablesNumber = 8;
    int fourChairsTablesNumber = 3;
    int timeToEndSimulationInMinutes = 1;

    int totalCustomersNumberCounter = 0;
    int resigningCustomersNumberCounter = 0;
    int insideCustomersNumberCounter = 0;
    int leavingCustomersNumberCounter = 0;
    int orderedDishesNumberCounter = 0;
    int preparedDishesNumberCounter = 0;
    int servedDishesNumberCounter = 0;
    int eatenDishesNumberCounter = 0;
    int droppedDishesNumberCounter = 0;

    bool loadIcon();
    void centerWindowOnDesktop();
public:
    Game();
    ~Game();
    void run();
    void updateScene();
    void changeScene();
};