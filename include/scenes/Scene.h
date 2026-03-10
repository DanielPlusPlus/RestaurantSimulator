#pragma once

#include <SFML/Graphics.hpp>

class Scene {
public:
    virtual void update(sf::RenderWindow& window, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};