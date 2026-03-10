#include "Game.h"
#include "scenes/MainMenu.h"

#include <SFML/Graphics.hpp>

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "3Civ Game", sf::Style::Titlebar | sf::Style::Close);
    this->currentScene = new MainMenu();
}

Game::~Game() {
    delete this->window;
    delete this->currentScene;
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        currentScene->update(*window, deltaTime);

        // window->clear();
        currentScene->render(*window);
        window->display();
    }
}

void Game::changeScene(int sceneID) {
    
}

