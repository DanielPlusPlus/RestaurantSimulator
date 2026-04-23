#include "Game.hpp"
#include "scenes/Level.hpp"
#include "scenes/MainMenu.hpp"

#include <algorithm>
#include <random>
#include <SFML/Graphics.hpp>


std::mt19937 globalRNG(std::random_device{}());

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(this->width * this->scaleFactor, 
                                        this->height * this->scaleFactor), 
                                        "Restaurant Simulator", 
                                        sf::Style::Titlebar | sf::Style::Close);
    loadIcon();
    centerWindowOnDesktop();
    this->currentScene = new MainMenu(&this->scaleFactor, &this->chefsNumber, 
                                      &this->waitersNumber, 
                                      &this->twoChairsTablesNumber, 
                                      &this->fourChairsTablesNumber, 
                                      &this->timeToEndSimulationInMinutes);
}

Game::~Game() {
    delete this->window;
    delete this->currentScene;
}

bool Game::loadIcon() {
    sf::Image icon;
    if (icon.loadFromFile("assets/icons/icon.png")) {
        this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        return true;
    }
    return false;
}

void Game::centerWindowOnDesktop() {
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const sf::Vector2u windowSize = window->getSize();

    const int positionX = std::max(0, (static_cast<int>(desktopMode.width) -
                                       static_cast<int>(windowSize.x)) / 2);
    const int positionY = std::max(0, (static_cast<int>(desktopMode.height) -
                                       static_cast<int>(windowSize.y)) / 2);

    window->setPosition(sf::Vector2i(positionX, positionY));
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        currentScene->update(5 * deltaTime, window);
        
        if(currentScene->changeScene(&this->newSceneName)) {
            updateScene();
        }
        
        currentScene->render(window);
        window->display();
    }
}

void Game::updateScene() {
    if(currentSceneName == newSceneName) {
        int newWindowWidth = width * scaleFactor;
        int newWindowHeight = height * scaleFactor; 

        window->setSize(sf::Vector2u(newWindowWidth, newWindowHeight));
        window->setView(sf::View(sf::FloatRect(0.0f, 0.0f,
                                               static_cast<float>(newWindowWidth),
                                               static_cast<float>(newWindowHeight))));
        centerWindowOnDesktop();
        changeScene();
    }
    else {
        changeScene();
        currentSceneName = newSceneName;
    }
}

void Game::changeScene() {
    delete this->currentScene;

    switch(newSceneName) {
        case ScenesEnum::MAIN_MENU:
            this->currentScene = new MainMenu(&this->scaleFactor, &this->chefsNumber, 
                                              &this->waitersNumber, 
                                              &this->twoChairsTablesNumber, 
                                              &this->fourChairsTablesNumber, 
                                              &this->timeToEndSimulationInMinutes);
            break;
        case ScenesEnum::LEVEL:
            this->currentScene = new Level(this->scaleFactor, this->chefsNumber, 
                                           this->waitersNumber, 
                                           this->twoChairsTablesNumber, 
                                           this->fourChairsTablesNumber, 
                                           this->timeToEndSimulationInMinutes);
            break;
        case ScenesEnum::SUMMARY:
            break;
        default:
            break;
    }
}