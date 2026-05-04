#pragma once

#include "Scene.hpp"


class Summary : public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RenderTexture blurRenderTexture;
    sf::Sprite blurSprite;
    sf::Font font;
    sf::Text titleText;
    sf::Text totalCustomersLabelText;
    sf::Text totalCustomersValueText;
    sf::Text resigningCustomersLabelText;
    sf::Text resigningCustomersValueText;
    sf::Text insideCustomersLabelText;
    sf::Text insideCustomersValueText;
    sf::Text leavingCustomersLabelText;
    sf::Text leavingCustomersValueText;
    sf::Text orderedDishesLabelText;
    sf::Text orderedDishesValueText;
    sf::Text preparedDishesLabelText;
    sf::Text preparedDishesValueText;
    sf::Text servedDishesLabelText;
    sf::Text servedDishesValueText;
    sf::Text eatenDishesLabelText;
    sf::Text eatenDishesValueText;
    sf::Text droppedDishesLabelText;
    sf::Text droppedDishesValueText;
    sf::Text returnText;
    bool texturesLoaded = false;
    bool fontLoaded = false;
    int fontSize = 12;
    float animTime = 0.0f;
    sf::Vector2u blurTextureSize = sf::Vector2u(0u, 0u);

    int waitersNumber = 0;
    int chefsNumber = 0;
    int twoChairsTablesNumber = 0;
    int fourChairsTablesNumber = 0;
    int simulationTimeInMinutes = 0;
    int totalCustomersNumberCounter = 0;
    int resigningCustomersNumberCounter = 0;
    int insideCustomersNumberCounter = 0;
    int leavingCustomersNumberCounter = 0;
    int orderedDishesNumberCounter = 0;
    int preparedDishesNumberCounter = 0;
    int servedDishesNumberCounter = 0;
    int eatenDishesNumberCounter = 0;
    int droppedDishesNumberCounter = 0;

    bool loadTextures(int scaleFactor) override;
    void writeStatsValues();
    void configureTextsStyles();
    void changeAnimation(float deltaTime);
    void updateTextsValues();
    void updateTextsPositions();
    bool isMouseOverText(sf::RenderWindow* window, sf::Text text);
    void updateHoverState(sf::RenderWindow* window);
    void handleMouseClick(sf::RenderWindow* window);
    void drawBackgroundWithBlur(sf::RenderWindow* window);
public:
    Summary(int scaleFactor,
            int chefsNumber,
            int waitersNumber,
            int twoChairsTablesNumber,
            int fourChairsTablesNumber,
            int simulationTimeInMinutes,
            int totalCustomersNumberCounter,
            int resigningCustomersNumberCounter,
            int insideCustomersNumberCounter,
            int leavingCustomersNumberCounter,
            int orderedDishesNumberCounter,
            int preparedDishesNumberCounter,
            int servedDishesNumberCounter,
            int eatenDishesNumberCounter,
            int droppedDishesNumberCounter);
    void update(float deltaTime, sf::RenderWindow* window) override;
    bool changeScene(enum ScenesEnum* sceneName) override;
    void render(sf::RenderWindow* window) override;
};