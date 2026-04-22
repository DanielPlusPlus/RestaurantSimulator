#pragma once

#include "Scene.hpp"

#include <SFML/Graphics.hpp>
#include <vector>



class MainMenu : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RenderTexture blurRenderTexture;
    sf::Sprite blurSprite;
    sf::Font font;
    sf::Text titleText;
    sf::Text scaleFactorLabelText;
    sf::Text scaleFactorValueText;
    sf::Text chefsNumberLabelText;
    sf::Text chefsNumberValueText;
    sf::Text waitersNumberLabelText;
    sf::Text waitersNumberValueText;
    sf::Text twoChairsTablesNumberLabelText;
    sf::Text twoChairsTablesNumberValueText;
    sf::Text fourChairsTablesNumberLabelText;
    sf::Text fourChairsTablesNumberValueText;
    sf::Text simulationTimeLabelText;
    sf::Text simulationTimeValueText;
    sf::Text startText;
    bool texturesLoaded = false;
    bool fontLoaded = false;
    int fontSize = 12;
    float animTime = 0.0f;
    sf::Vector2u blurTextureSize = sf::Vector2u(0u, 0u);

    int* scaleFactorPtr;
    int* chefsNumberPtr;
    int* waitersNumberPtr;
    int* twoChairsTablesNumberPtr;
    int* fourChairsTablesNumberPtr;
    int* simulationTimePtr;

    int newScaleFactor = 1;
    int newChefsNumber = 1;
    int newWaitersNumber = 1;
    int newTwoChairsTablesNumber = 8;
    int newFourChairsTablesNumber = 3;
    int newSimulationTimeInMinutes = 1;

    bool isSceneToReload = false;

    void configureTextsStyles();
    void loadInitValues();
    void changeAnimation(float deltaTime);
    void updateValuesTexts();
    void updateTextsPositions();
    bool isMouseOverText(sf::RenderWindow* window, sf::Text text);
    void updateHoverState(sf::RenderWindow* window);
    void handleMouseClick(sf::RenderWindow* window);
    void drawBackgroundWithBlur(sf::RenderWindow* window);

    bool loadTextures(int scaleFactor) override;
public:
    MainMenu(int* scaleFactor, int* chefsNumberPtr, 
             int* waitersNumberPtr, int* twoChairsTablesNumberPtr, 
             int* fourChairsTablesNumberPtr, int* simulationTimePtr);
    ~MainMenu();
    void update(float deltaTime, sf::RenderWindow* window) override;
    bool changeScene(enum ScenesEnum* sceneName) override;
    void render(sf::RenderWindow* window) override;
};