#include "scenes/MainMenu.hpp"
#include "utils/InitFileReader.hpp"
#include "utils/InitFileWriter.hpp"

#include <algorithm>
#include <cmath>
#include <string>


MainMenu::MainMenu(int* scaleFactor, int* chefsNumberPtr, 
                   int* waitersNumberPtr, int* twoChairsTablesNumberPtr, 
                   int* fourChairsTablesNumberPtr, int* simulationTimePtr) : 
                   Scene(*scaleFactor), scaleFactorPtr(scaleFactor), 
                   chefsNumberPtr(chefsNumberPtr), 
                   waitersNumberPtr(waitersNumberPtr), 
                   twoChairsTablesNumberPtr(twoChairsTablesNumberPtr),
                   fourChairsTablesNumberPtr(fourChairsTablesNumberPtr),
                   simulationTimePtr(simulationTimePtr) {
    texturesLoaded = loadTextures(this->scaleFactor);
    loadInitValues();
    if(fontLoaded) {
        configureTextsStyles();
        updateValuesTexts();
    }
}

MainMenu::~MainMenu() {
    InitFileWriter initFileWriter(*scaleFactorPtr, *chefsNumberPtr, 
                                  *waitersNumberPtr, *twoChairsTablesNumberPtr, 
                                  *fourChairsTablesNumberPtr, *simulationTimePtr);
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
    const unsigned int baseOptionTextSize = static_cast<unsigned int>(fontSize + 2);
    const unsigned int baseTitleTextSize = static_cast<unsigned int>(fontSize + 12);
    const unsigned int baseStartTextSize = static_cast<unsigned int>(fontSize + 6);

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

    twoChairsTablesNumberLabelText.setFont(font);
    twoChairsTablesNumberLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    twoChairsTablesNumberLabelText.setString("2 Chairs Tables Number:");
    twoChairsTablesNumberLabelText.setFillColor(sf::Color(245, 233, 190));
    twoChairsTablesNumberLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    twoChairsTablesNumberLabelText.setOutlineColor(outlineColor);

    twoChairsTablesNumberValueText.setFont(font);
    twoChairsTablesNumberValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    twoChairsTablesNumberValueText.setFillColor(sf::Color(255, 222, 120));
    twoChairsTablesNumberValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    twoChairsTablesNumberValueText.setOutlineColor(outlineColor);

    fourChairsTablesNumberLabelText.setFont(font);
    fourChairsTablesNumberLabelText.setCharacterSize(baseOptionTextSize * scaleFactor);
    fourChairsTablesNumberLabelText.setString("4 Chairs Tables Number:");
    fourChairsTablesNumberLabelText.setFillColor(sf::Color(245, 233, 190));
    fourChairsTablesNumberLabelText.setOutlineThickness(static_cast<float>(scaleFactor));
    fourChairsTablesNumberLabelText.setOutlineColor(outlineColor);

    fourChairsTablesNumberValueText.setFont(font);
    fourChairsTablesNumberValueText.setCharacterSize(baseOptionTextSize * scaleFactor);
    fourChairsTablesNumberValueText.setFillColor(sf::Color(255, 222, 120));
    fourChairsTablesNumberValueText.setOutlineThickness(static_cast<float>(scaleFactor));
    fourChairsTablesNumberValueText.setOutlineColor(outlineColor);

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
    newTwoChairsTablesNumber = configValues["twoChairsTablesNumber"];
    newFourChairsTablesNumber = configValues["fourChairsTablesNumber"];
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
    *twoChairsTablesNumberPtr = std::max(1, std::min(newTwoChairsTablesNumber, 8));
    *fourChairsTablesNumberPtr = std::max(1, std::min(newFourChairsTablesNumber, 3));
    *simulationTimePtr = std::max(1, std::min(newSimulationTimeInMinutes, 5));

    scaleFactorValueText.setString(std::to_string(*scaleFactorPtr));
    chefsNumberValueText.setString(std::to_string(*chefsNumberPtr));
    waitersNumberValueText.setString(std::to_string(*waitersNumberPtr));
    twoChairsTablesNumberValueText.setString(std::to_string(*twoChairsTablesNumberPtr));
    fourChairsTablesNumberValueText.setString(std::to_string(*fourChairsTablesNumberPtr));
    simulationTimeValueText.setString(std::to_string(*simulationTimePtr) + " min");
}

void MainMenu::updateTextsPositions() {

    const auto scaled = [this](float referenceValue) {
        return referenceValue * static_cast<float>(scaleFactor);
    };

    const float centerX = scaled(151.0f);
    const float titleY = scaled(34.0f);
    const float valueSpacing = scaled(12.0f);
    const float startY = scaled(200.0f);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(centerX, titleY);

    const sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setOrigin(startBounds.left + startBounds.width / 2.0f,
                        startBounds.top + startBounds.height / 2.0f);

    const float titleBottom = titleY + titleBounds.height / 2.0f;
    const float startTop = startY - startBounds.height / 2.0f;

    auto optionRowHeight = [](const sf::Text& labelText, const sf::Text& valueText) {
        const sf::FloatRect labelBounds = labelText.getLocalBounds();
        const sf::FloatRect valueBounds = valueText.getLocalBounds();
        return std::max(labelBounds.height, valueBounds.height);
    };

    const float scaleFactorRowHeight = optionRowHeight(scaleFactorLabelText, scaleFactorValueText);
    const float chefsNumberRowHeight = optionRowHeight(chefsNumberLabelText, chefsNumberValueText);
    const float waitersNumberRowHeight = optionRowHeight(waitersNumberLabelText, waitersNumberValueText);
    const float twoChairsTablesRowHeight = optionRowHeight(twoChairsTablesNumberLabelText,
                                                           twoChairsTablesNumberValueText);
    const float fourChairsTablesRowHeight = optionRowHeight(fourChairsTablesNumberLabelText,
                                                            fourChairsTablesNumberValueText);
    const float simulationTimeRowHeight = optionRowHeight(simulationTimeLabelText,
                                                          simulationTimeValueText);

    const float optionsTotalHeight = scaleFactorRowHeight + chefsNumberRowHeight +
                                     waitersNumberRowHeight + twoChairsTablesRowHeight +
                                     fourChairsTablesRowHeight + simulationTimeRowHeight;
    const float equalGap = (startTop - titleBottom - optionsTotalHeight) / 7.0f;

    const float scaleFactorOptionTop = titleBottom + equalGap;
    const float chefsNumberOptionTop = scaleFactorOptionTop + scaleFactorRowHeight + equalGap;
    const float waitersNumberOptionTop = chefsNumberOptionTop + chefsNumberRowHeight + equalGap;
    const float twoChairsTablesOptionTop = waitersNumberOptionTop + waitersNumberRowHeight + equalGap;
    const float fourChairsTablesOptionTop = twoChairsTablesOptionTop + twoChairsTablesRowHeight + equalGap;
    const float simulationTimeOptionTop = fourChairsTablesOptionTop + fourChairsTablesRowHeight + equalGap;

    auto positionOption = [centerX, valueSpacing](sf::Text& labelText, sf::Text& valueText, 
                                                  float topY) {
        const sf::FloatRect labelBounds = labelText.getLocalBounds();
        const sf::FloatRect valueBounds = valueText.getLocalBounds();
        
        const float totalWidth = labelBounds.width + valueSpacing + valueBounds.width;
        const float leftX = centerX - (totalWidth / 2.0f);

        labelText.setPosition(leftX - labelBounds.left, topY - labelBounds.top);
        valueText.setPosition(leftX + labelBounds.width + valueSpacing - valueBounds.left,
                              topY - valueBounds.top);
    };

    positionOption(scaleFactorLabelText, scaleFactorValueText, 
                   scaleFactorOptionTop);
    positionOption(chefsNumberLabelText, chefsNumberValueText, 
                   chefsNumberOptionTop);
    positionOption(waitersNumberLabelText, waitersNumberValueText, 
                   waitersNumberOptionTop);
    positionOption(twoChairsTablesNumberLabelText, twoChairsTablesNumberValueText, 
                   twoChairsTablesOptionTop);
    positionOption(fourChairsTablesNumberLabelText, fourChairsTablesNumberValueText, 
                   fourChairsTablesOptionTop);
    positionOption(simulationTimeLabelText, simulationTimeValueText, 
                   simulationTimeOptionTop);
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
    fourChairsTablesNumberValueText.setFillColor(isMouseOverText(window, fourChairsTablesNumberValueText) ? 
                                                 hoverValueColor : normalValueColor);
    twoChairsTablesNumberValueText.setFillColor(isMouseOverText(window, twoChairsTablesNumberValueText) ? 
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
    if(isMouseOverText(window, twoChairsTablesNumberValueText)) {
        newTwoChairsTablesNumber = 1 + newTwoChairsTablesNumber % 8;
        updateValuesTexts();
        return;
    }
    if(isMouseOverText(window, fourChairsTablesNumberValueText)) {
        newFourChairsTablesNumber = 1 + newFourChairsTablesNumber % 3;
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
    window->draw(twoChairsTablesNumberLabelText);
    window->draw(twoChairsTablesNumberValueText);
    window->draw(fourChairsTablesNumberLabelText);
    window->draw(fourChairsTablesNumberValueText);
    window->draw(simulationTimeLabelText);
    window->draw(simulationTimeValueText);
    window->draw(startText);
}