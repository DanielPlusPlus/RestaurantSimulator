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
    int scaleFactor = 1;
    int chefsNumber = 1;
    int waitersNumber = 1;
    int twoChairsTablesNumber = 8;
    int fourChairsTablesNumber = 3;
    int timeToEndSimulationInMinutes = 1;
    sf::RenderWindow* window;
    Scene* currentScene;
    bool loadIcon();
    void centerWindowOnDesktop();
public:
    Game();
    ~Game();
    void run();
    void updateScene();
    void changeScene();
};