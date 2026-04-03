#pragma once

#include "structures/Positions.hpp"
#include "structures/CharactersTexturesPaths.hpp"
#include "enums/DirectionsEnum.hpp"

#include <SFML/Graphics.hpp>


class Character {
public:
    virtual void update(float deltaTime, int scaleFactor) = 0;
    virtual void render(sf::RenderWindow* window) = 0;
};