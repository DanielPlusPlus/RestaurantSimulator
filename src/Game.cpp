#include "Game.hpp"
#include "scenes/Level.hpp"

#include <random>
#include <SFML/Graphics.hpp>


std::mt19937 globalRNG(std::random_device{}());

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(this->width * this->scaleFactor, this->height * this->scaleFactor), "Restaurant Simulator", sf::Style::Titlebar | sf::Style::Close);
    this->currentScene = new Level(this->scaleFactor);
}

Game::~Game() {
    delete this->window;
    delete this->currentScene;
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        currentScene->update(deltaTime * 2);
        
        // window->clear();
        currentScene->render(window);
        window->display();
    }
}

void Game::changeScene(int sceneID) {
    
}

