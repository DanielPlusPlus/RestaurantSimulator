#pragma once

#include "scenes/Scene.hpp"

#include <SFML/Graphics.hpp>


class Game {
private:
    int width = 302;
    int height = 234;
    int scaleFactor = 4;
    sf::RenderWindow* window;
    Scene* currentScene;
public:
    Game();
    ~Game();
    void run();
    void changeScene(int sceneID);
};