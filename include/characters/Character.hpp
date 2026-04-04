#pragma once

#include "structures/Positions.hpp"
#include "structures/CharactersTexturesPaths.hpp"
#include "enums/DirectionsEnum.hpp"

#include <SFML/Graphics.hpp>


class Character {
protected:
    Positions startPositions;
    Positions positions;
public:
    Character(Positions positions) : startPositions(positions), positions(positions) {}
    float getYPos() {
        return positions.yPos; 
    };
    virtual void update(float deltaTime, int scaleFactor) = 0;
    virtual void render(sf::RenderWindow* window) = 0;
};