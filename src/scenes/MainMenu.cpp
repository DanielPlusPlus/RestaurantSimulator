#include "scenes/MainMenu.h"
#include "scenes/Scene.h"

#include <SFML/Graphics.hpp>

void MainMenu::update(sf::RenderWindow& window, float deltaTime) {
    this->timeElapsed += deltaTime;
    
    if (int(timeElapsed) % 10 < 5) {
        window.clear(sf::Color::White);
    }
    else {
        window.clear(sf::Color::Black);
    }

    if (this->timeElapsed >= 10.0f) {
        this->timeElapsed = 0.0f;
    }
}

void MainMenu::render(sf::RenderWindow& window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();
    }
}