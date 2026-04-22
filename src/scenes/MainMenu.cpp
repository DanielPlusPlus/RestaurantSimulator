#include "scenes/MainMenu.hpp"
#include "utils/InitFileReader.hpp"
#include "utils/InitFileWriter.hpp"

#include <algorithm>
#include <cmath>
#include <string>


MainMenu::MainMenu(int* scaleFactor, int* chefsNumberPtr, 
                   int* waitersNumberPtr, int* simulationTimePtr) : 
                   Scene(*scaleFactor), scaleFactorPtr(scaleFactor), 
                   chefsNumberPtr(chefsNumberPtr), 
                   waitersNumberPtr(waitersNumberPtr), 
                   simulationTimePtr(simulationTimePtr) {
    texturesLoaded = loadTextures(this->scaleFactor);
    loadInitValues();
    if(fontLoaded) {
        configureTextsStyles();
        updateValuesTexts();
    }
}

MainMenu::~MainMenu() {
    InitFileWriter initFileWriter(*scaleFactorPtr, *chefsNumberPtr, *waitersNumberPtr, *simulationTimePtr);
    initFileWriter.createConfigFile();
}

bool MainMenu::loadTextures(int scaleFactor) {
    if(!backgroundTexture.loadFromFile("assets/backgrounds/background.png")) {
        return false;
    }
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if(!font.loadFromFile("assets/fonts/determination.ttf")) {
        return false;
    }
    fontLoaded = true;

    return true;
}

void MainMenu::configureTextsStyles() {
    const unsigned int baseOptionTextSize = static_cast<unsigned int>(fontSize + 4);
    const unsigned int baseTitleTextSize = static_cast<unsigned int>(fontSize + 12);
    const unsigned int baseStartTextSize = static_cast<unsigned int>(fontSize + 8);

    const sf::Color outlineColor(58, 58, 80);
    titleText.setFont(font);
    titleText.setCharacterSize(baseTitleTextSize * scaleFactor);
    titleText.setString("Restaurant Simulator");
    titleText.setFillColor(sf::Color(252, 247, 220));
    titleText.setOutlineThickness(1.5f * static_cast<float>(scaleFactor));
    titleText.setOutlineColor(outlineColor);

    scaleFactorLabelText.setFont(font);
    scaleFactorLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    scaleFactorLabelText.setString("Scale Factor:");
    scaleFactorLabelText.setFillColor(sf::Color(245, 233, 190));
    scaleFactorLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    scaleFactorLabelText.setOutlineColor(outlineColor);

    scaleFactorValueText.setFont(font);
    scaleFactorValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    scaleFactorValueText.setFillColor(sf::Color(255, 222, 120));
    scaleFactorValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    scaleFactorValueText.setOutlineColor(outlineColor);

    chefsNumberLabelText.setFont(font);
    chefsNumberLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    chefsNumberLabelText.setString("Chefs Number:");
    chefsNumberLabelText.setFillColor(sf::Color(245, 233, 190));
    chefsNumberLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    chefsNumberLabelText.setOutlineColor(outlineColor);

    chefsNumberValueText.setFont(font);
    chefsNumberValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    chefsNumberValueText.setFillColor(sf::Color(255, 222, 120));
    chefsNumberValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    chefsNumberValueText.setOutlineColor(outlineColor);

    waitersNumberLabelText.setFont(font);
    waitersNumberLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    waitersNumberLabelText.setString("Waiters Number:");
    waitersNumberLabelText.setFillColor(sf::Color(245, 233, 190));
    waitersNumberLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    waitersNumberLabelText.setOutlineColor(outlineColor);

    waitersNumberValueText.setFont(font);
    waitersNumberValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    waitersNumberValueText.setFillColor(sf::Color(255, 222, 120));
    waitersNumberValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    waitersNumberValueText.setOutlineColor(outlineColor);

    simulationTimeLabelText.setFont(font);
    simulationTimeLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    simulationTimeLabelText.setString("Simulation Time:");
    simulationTimeLabelText.setFillColor(sf::Color(245, 233, 190));
    simulationTimeLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    simulationTimeLabelText.setOutlineColor(outlineColor);

    simulationTimeValueText.setFont(font);
    simulationTimeValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    simulationTimeValueText.setFillColor(sf::Color(255, 222, 120));
    simulationTimeValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    simulationTimeValueText.setOutlineColor(outlineColor);

    startText.setFont(font);
    startText.setCharacterSize(baseStartTextSize * scaleFactor);
    startText.setString("START");
    startText.setFillColor(sf::Color(255, 236, 141));
    startText.setOutlineThickness(1.3f * static_cast<float>(scaleFactor));
    startText.setOutlineColor(outlineColor);
}

void MainMenu::loadInitValues() {
    InitFileReader initFileReader;
    std::unordered_map<std::string, int> configValues = initFileReader.getConfigValues();
    newScaleFactor = configValues["scaleFactor"];
    newChefsNumber = configValues["chefsNumber"];
    newWaitersNumber = configValues["waitersNumber"];
    newSimulationTimeInMinutes = configValues["timeToEndSimulationInMinutes"];
    if(newScaleFactor != scaleFactor) {
        isSceneToReload = true;
    }
}

void MainMenu::update(float deltaTime, sf::RenderWindow* window) {
    sf::Event event;
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window->close();
        }
        if(event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(window);
        }
    }
    changeAnimation(deltaTime);
    updateTextsPositions();
    updateHoverState(window);
}

void MainMenu::changeAnimation(float deltaTime) {
    animTime += deltaTime;
    animTime = std::fmod(animTime + deltaTime, 1000.0f);

    const float pulse = 1.0f + 0.035f * std::sin(animTime * 2.7f);
    titleText.setScale(pulse, pulse);

    const float wave = 0.5f + 0.5f * std::sin(animTime * 4.0f);
    const sf::Uint8 green = static_cast<sf::Uint8>(200.0f + 40.0f * wave);
    titleText.setFillColor(sf::Color(252, green, 180));

    const float startPulse = 0.95f + 0.08f * (0.5f + 0.5f * std::sin(animTime * 5.0f));
    startText.setScale(startPulse, startPulse);
}

void MainMenu::updateValuesTexts() {
    *scaleFactorPtr = std::max(1, std::min(newScaleFactor, 9));
    *chefsNumberPtr = std::max(1, std::min(newChefsNumber, 3));
    *waitersNumberPtr = std::max(1, std::min(newWaitersNumber, 3));
    *simulationTimePtr = std::max(1, std::min(newSimulationTimeInMinutes, 5));

    scaleFactorValueText.setString(std::to_string(*scaleFactorPtr));
    chefsNumberValueText.setString(std::to_string(*chefsNumberPtr));
    waitersNumberValueText.setString(std::to_string(*waitersNumberPtr));
    simulationTimeValueText.setString(std::to_string(*simulationTimePtr) + " min");
}

void MainMenu::updateTextsPositions() {

    const auto scaled = [this](float referenceValue) {
        return referenceValue * static_cast<float>(scaleFactor);
    };

    const float centerX = scaled(151.0f);
    const float titleY = scaled(38.0f);
    const float scaleFactorOptionY = scaled(84.0f);
    const float chefsNumberOptionY = scaled(106.0f);
    const float waitersNumberOptionY = scaled(128.0f);
    const float simulationTimeOptionY = scaled(150.0f);
    const float valueSpacing = scaled(12.0f);
    const float startY = scaled(197.0f);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(centerX, titleY);

    auto positionOption = [centerX, valueSpacing](sf::Text& labelText, sf::Text& valueText, 
                                                  float yPos) {
        const sf::FloatRect labelBounds = labelText.getLocalBounds();
        const sf::FloatRect valueBounds = valueText.getLocalBounds();
        
        const float totalWidth = labelBounds.width + valueSpacing + valueBounds.width;
        const float leftX = centerX - (totalWidth / 2.0f);

        labelText.setPosition(leftX - labelBounds.left, yPos);
        valueText.setPosition(leftX + labelBounds.width + valueSpacing - valueBounds.left, yPos);
    };

    positionOption(scaleFactorLabelText, scaleFactorValueText, 
                   scaleFactorOptionY);
    positionOption(chefsNumberLabelText, chefsNumberValueText, 
                   chefsNumberOptionY);
    positionOption(waitersNumberLabelText, waitersNumberValueText, 
                   waitersNumberOptionY);
    positionOption(simulationTimeLabelText, simulationTimeValueText, 
                   simulationTimeOptionY);

    const sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setOrigin(startBounds.left + startBounds.width / 2.0f,
                        startBounds.top + startBounds.height / 2.0f);
    startText.setPosition(centerX, startY);
}

bool MainMenu::isMouseOverText(sf::RenderWindow* window, sf::Text text) {
    const sf::Vector2i mousePositions = sf::Mouse::getPosition(*window);
    const sf::Vector2f mouseWindowPositions = window->mapPixelToCoords(mousePositions);
    return text.getGlobalBounds().contains(mouseWindowPositions);
}

void MainMenu::updateHoverState(sf::RenderWindow* window) {
    const sf::Color normalValueColor(255, 222, 120);
    const sf::Color hoverValueColor(255, 255, 190);
    const sf::Color normalStartColor(255, 236, 141);
    const sf::Color hoverStartColor(255, 255, 210);

    scaleFactorValueText.setFillColor(isMouseOverText(window, scaleFactorValueText) ? 
                                      hoverValueColor : normalValueColor);
    chefsNumberValueText.setFillColor(isMouseOverText(window, chefsNumberValueText) ? 
                                      hoverValueColor : normalValueColor);
    waitersNumberValueText.setFillColor(isMouseOverText(window, waitersNumberValueText) ? 
                                        hoverValueColor : normalValueColor);
    simulationTimeValueText.setFillColor(isMouseOverText(window, simulationTimeValueText) ? 
                                         hoverValueColor : normalValueColor);
    startText.setFillColor(isMouseOverText(window, startText) ? hoverStartColor : 
                           normalStartColor);
}

void MainMenu::handleMouseClick(sf::RenderWindow* window) {
    if(isMouseOverText(window, scaleFactorValueText)) {
        newScaleFactor = 1 + newScaleFactor % 9;
        updateValuesTexts();
        isSceneToReload = true;
        return;
    }
    if(isMouseOverText(window, chefsNumberValueText)) {
        newChefsNumber = 1 + newChefsNumber % 3;
        updateValuesTexts();
        return;
    }
    if(isMouseOverText(window, waitersNumberValueText)) {
        newWaitersNumber = 1 + newWaitersNumber % 3;
        updateValuesTexts();
        return;
    }
    if(isMouseOverText(window, simulationTimeValueText)) {
        newSimulationTimeInMinutes = 1 + newSimulationTimeInMinutes % 5;
        updateValuesTexts();
        return;
    }
    if(isMouseOverText(window, startText)) {
        isSceneToChange = true;
    }
}

void MainMenu::drawBackgroundWithBlur(sf::RenderWindow* window) {
    const sf::Vector2u windowSize = window->getSize();
    const float downsampleFactor = 1.45f;
    const unsigned int reducedWidth = std::max(1u, static_cast<unsigned int>(
        std::round(static_cast<float>(windowSize.x) / downsampleFactor)));
    const unsigned int reducedHeight = std::max(1u, static_cast<unsigned int>(
        std::round(static_cast<float>(windowSize.y) / downsampleFactor)));

    if(blurTextureSize.x != reducedWidth || blurTextureSize.y != reducedHeight) {
        if (!blurRenderTexture.create(reducedWidth, reducedHeight)) {
            backgroundSprite.setPosition(0.0f, 0.0f);
            backgroundSprite.setColor(sf::Color::White);
            window->draw(backgroundSprite);
            return;
        }
        blurRenderTexture.setSmooth(true);
        blurTextureSize = sf::Vector2u(reducedWidth, reducedHeight);
    }

    sf::Sprite reducedBackground = backgroundSprite;
    reducedBackground.setPosition(0.0f, 0.0f);
    reducedBackground.setScale(
        backgroundSprite.getScale().x * (static_cast<float>(reducedWidth) / 
                                         static_cast<float>(windowSize.x)),
        backgroundSprite.getScale().y * (static_cast<float>(reducedHeight) / 
                                         static_cast<float>(windowSize.y)));

    blurRenderTexture.clear(sf::Color::Transparent);
    blurRenderTexture.draw(reducedBackground);
    blurRenderTexture.display();

    backgroundSprite.setPosition(0.0f, 0.0f);
    backgroundSprite.setColor(sf::Color::White);
    window->draw(backgroundSprite);

    blurSprite.setTexture(blurRenderTexture.getTexture(), true);
    blurSprite.setPosition(0.0f, 0.0f);
    blurSprite.setScale(static_cast<float>(windowSize.x) / static_cast<float>(reducedWidth),
                        static_cast<float>(windowSize.y) / static_cast<float>(reducedHeight));
    blurSprite.setColor(sf::Color(255, 255, 255, 80));
    window->draw(blurSprite);

    sf::RectangleShape blurVeil(sf::Vector2f(static_cast<float>(windowSize.x),
                                             static_cast<float>(windowSize.y)));
    blurVeil.setFillColor(sf::Color(18, 18, 24, 10));
    window->draw(blurVeil);
}

bool MainMenu::changeScene(enum ScenesEnum* sceneName) {
    if(isSceneToReload) {
        *sceneName = ScenesEnum::MAIN_MENU;
        return true;
    }
    if(isSceneToChange) {
        *sceneName = ScenesEnum::LEVEL;
        return true;
    }
    return false;
}

void MainMenu::render(sf::RenderWindow* window) {
    drawBackgroundWithBlur(window);

    window->draw(titleText);
    window->draw(scaleFactorLabelText);
    window->draw(scaleFactorValueText);
    window->draw(chefsNumberLabelText);
    window->draw(chefsNumberValueText);
    window->draw(waitersNumberLabelText);
    window->draw(waitersNumberValueText);
    window->draw(simulationTimeLabelText);
    window->draw(simulationTimeValueText);
    window->draw(startText);
}