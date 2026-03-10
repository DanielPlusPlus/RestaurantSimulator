#pragma once

#include "scenes/Scene.h"

#include <SFML/Graphics.hpp>

class Game {
private:
    int width = 1280;
    int height = 720;
    sf::RenderWindow* window;
    Scene* currentScene;
public:
    Game();
    ~Game();
    void run();
    void changeScene(int sceneID);
};