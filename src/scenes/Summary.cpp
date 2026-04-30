#include "scenes/Summary.hpp"

#include "utils/StatsFileWriter.hpp"

#include <algorithm>
#include <cmath>
#include <string>


Summary::Summary(int scaleFactor, 
                 int waitersNumber, 
                 int chefsNumber,
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
                 int droppedDishesNumberCounter
                 ) : Scene(scaleFactor),
                     waitersNumber(waitersNumber),
                     chefsNumber(chefsNumber),
                     twoChairsTablesNumber(twoChairsTablesNumber),
                     fourChairsTablesNumber(fourChairsTablesNumber), 
                     simulationTimeInMinutes(simulationTimeInMinutes), 
                     totalCustomersNumberCounter(totalCustomersNumberCounter),
                     resigningCustomersNumberCounter(resigningCustomersNumberCounter),
                     insideCustomersNumberCounter(insideCustomersNumberCounter),
                     leavingCustomersNumberCounter(leavingCustomersNumberCounter),
                     orderedDishesNumberCounter(orderedDishesNumberCounter),
                     preparedDishesNumberCounter(preparedDishesNumberCounter),
                     servedDishesNumberCounter(servedDishesNumberCounter),
                     eatenDishesNumberCounter(eatenDishesNumberCounter),
                     droppedDishesNumberCounter(droppedDishesNumberCounter) {
    writeStatsValues();
    texturesLoaded = loadTextures(scaleFactor);
    if(fontLoaded) {
        configureTextsStyles();
        updateTextsValues();
    }
}

void Summary::writeStatsValues() {
    StatsFileWriter statsFileWriter(waitersNumber,
                                    chefsNumber,
                                    twoChairsTablesNumber,
                                    fourChairsTablesNumber,
                                    simulationTimeInMinutes,
                                    totalCustomersNumberCounter,
                                    resigningCustomersNumberCounter,
                                    insideCustomersNumberCounter,
                                    leavingCustomersNumberCounter,
                                    orderedDishesNumberCounter,
                                    preparedDishesNumberCounter,
                                    servedDishesNumberCounter,
                                    eatenDishesNumberCounter,
                                    droppedDishesNumberCounter);
    statsFileWriter.writeStatsToFile();
}

bool Summary::loadTextures(int scaleFactor) {
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

void Summary::configureTextsStyles() {
    const unsigned int baseOptionTextSize = static_cast<unsigned int>(fontSize - 2);
    const unsigned int baseTitleTextSize = static_cast<unsigned int>(fontSize + 10);
    const unsigned int baseReturnTextSize = static_cast<unsigned int>(fontSize + 6);

    const sf::Color labelColor(245, 233, 190);
    const sf::Color valueColor(255, 222, 120);
    const sf::Color outlineColor(58, 58, 80);

    titleText.setFont(font);
    titleText.setCharacterSize(baseTitleTextSize * scaleFactor);
    titleText.setString("Final Statistics");
    titleText.setFillColor(sf::Color(252, 247, 220));
    titleText.setOutlineThickness(1.4f * static_cast<float>(scaleFactor));
    titleText.setOutlineColor(outlineColor);

    auto configureLabel = [&](sf::Text& text, const std::string& label) {
        text.setFont(font);
        text.setCharacterSize(baseOptionTextSize * scaleFactor);
        text.setString(label);
        text.setFillColor(labelColor);
        text.setOutlineThickness(static_cast<float>(scaleFactor));
        text.setOutlineColor(outlineColor);
    };

    auto configureValue = [&](sf::Text& text) {
        text.setFont(font);
        text.setCharacterSize(baseOptionTextSize * scaleFactor);
        text.setFillColor(valueColor);
        text.setOutlineThickness(static_cast<float>(scaleFactor));
        text.setOutlineColor(outlineColor);
    };

    configureLabel(totalCustomersLabelText, "Total Customers:");
    configureValue(totalCustomersValueText);
    configureLabel(resigningCustomersLabelText, "Resigning Customers:");
    configureValue(resigningCustomersValueText);
    configureLabel(insideCustomersLabelText, "Inside Customers:");
    configureValue(insideCustomersValueText);
    configureLabel(leavingCustomersLabelText, "Leaving Customers:");
    configureValue(leavingCustomersValueText);

    configureLabel(orderedDishesLabelText, "Ordered Dishes:");
    configureValue(orderedDishesValueText);
    configureLabel(preparedDishesLabelText, "Prepared Dishes:");
    configureValue(preparedDishesValueText);
    configureLabel(servedDishesLabelText, "Served Dishes:");
    configureValue(servedDishesValueText);
    configureLabel(eatenDishesLabelText, "Eaten Dishes:");
    configureValue(eatenDishesValueText);
    configureLabel(droppedDishesLabelText, "Dropped Dishes:");
    configureValue(droppedDishesValueText);

    returnText.setFont(font);
    returnText.setCharacterSize(baseReturnTextSize * scaleFactor);
    returnText.setString("Return to Menu");
    returnText.setFillColor(sf::Color(255, 236, 141));
    returnText.setOutlineThickness(1.3f * static_cast<float>(scaleFactor));
    returnText.setOutlineColor(outlineColor);
}

void Summary::changeAnimation(float deltaTime) {
    animTime += deltaTime;
    animTime = std::fmod(animTime + deltaTime, 1000.0f);

    const float startPulse = 0.95f + 0.08f * (0.5f + 0.5f * std::sin(animTime * 5.0f));
    returnText.setScale(startPulse, startPulse);
}

void Summary::updateTextsValues() {
    totalCustomersValueText.setString(std::to_string(totalCustomersNumberCounter));
    resigningCustomersValueText.setString(std::to_string(resigningCustomersNumberCounter));
    insideCustomersValueText.setString(std::to_string(insideCustomersNumberCounter));
    leavingCustomersValueText.setString(std::to_string(leavingCustomersNumberCounter));
    orderedDishesValueText.setString(std::to_string(orderedDishesNumberCounter));
    preparedDishesValueText.setString(std::to_string(preparedDishesNumberCounter));
    servedDishesValueText.setString(std::to_string(servedDishesNumberCounter));
    eatenDishesValueText.setString(std::to_string(eatenDishesNumberCounter));
    droppedDishesValueText.setString(std::to_string(droppedDishesNumberCounter));
}

void Summary::updateTextsPositions() {
    const auto scaled = [this](float referenceValue) {
        return referenceValue * static_cast<float>(scaleFactor);
    };

    const float margin = scaled(8.0f);
    const float leftEdge = margin;
    const float rightEdge = static_cast<float>(302 * scaleFactor) - margin;
    const float centerX = scaled(151.0f);
    const float titleY = scaled(34.0f);
    const float returnY = scaled(200.0f);
    const float valueSpacing = scaled(12.0f);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
                        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(centerX, titleY);

    const sf::FloatRect returnBounds = returnText.getLocalBounds();
    returnText.setOrigin(returnBounds.left + returnBounds.width / 2.0f,
                         returnBounds.top + returnBounds.height / 2.0f);
    returnText.setPosition(centerX, returnY);

    auto textTopOffset = [](const sf::Text& text) {
        const sf::FloatRect bounds = text.getLocalBounds();
        return -bounds.top;
    };

    auto textTotalHeight = [&](const sf::Text& text) {
        const sf::FloatRect bounds = text.getLocalBounds();
        return textTopOffset(text) + bounds.height;
    };

    struct RowMetrics {
        float height;
        float topOffset;
    };

    auto rowMetricsBoth = [&](const sf::Text& leftLabel, const sf::Text& leftValue,
                              const sf::Text& rightLabel, const sf::Text& rightValue) {
        const float leftLabelTop = textTopOffset(leftLabel);
        const float leftValueTop = textTopOffset(leftValue);
        const float rightLabelTop = textTopOffset(rightLabel);
        const float rightValueTop = textTopOffset(rightValue);
        const float topOffset = std::max({leftLabelTop, leftValueTop, rightLabelTop, rightValueTop});
        const float height = std::max({
            textTotalHeight(leftLabel),
            textTotalHeight(leftValue),
            textTotalHeight(rightLabel),
            textTotalHeight(rightValue)
        });
        return RowMetrics{height, topOffset};
    };

    auto rowMetricsSingle = [&](const sf::Text& labelText, const sf::Text& valueText) {
        const float labelTop = textTopOffset(labelText);
        const float valueTop = textTopOffset(valueText);
        const float topOffset = std::max(labelTop, valueTop);
        const float height = std::max(textTotalHeight(labelText), textTotalHeight(valueText));
        return RowMetrics{height, topOffset};
    };

    const RowMetrics row1Metrics = rowMetricsBoth(totalCustomersLabelText, totalCustomersValueText,
                                                  orderedDishesLabelText, orderedDishesValueText);
    const RowMetrics row2Metrics = rowMetricsBoth(resigningCustomersLabelText, resigningCustomersValueText,
                                                  preparedDishesLabelText, preparedDishesValueText);
    const RowMetrics row3Metrics = rowMetricsBoth(insideCustomersLabelText, insideCustomersValueText,
                                                  servedDishesLabelText, servedDishesValueText);
    const RowMetrics row4Metrics = rowMetricsBoth(leavingCustomersLabelText, leavingCustomersValueText,
                                                  eatenDishesLabelText, eatenDishesValueText);
    const RowMetrics row5Metrics = rowMetricsSingle(droppedDishesLabelText, droppedDishesValueText);

    const float rowsTotalHeight = row1Metrics.height + row2Metrics.height + row3Metrics.height +
                                  row4Metrics.height + row5Metrics.height;
    const float titleBottom = titleY + titleBounds.height / 2.0f;
    const float returnTop = returnY - returnBounds.height / 2.0f;
    const float equalGap = (returnTop - titleBottom - rowsTotalHeight) / 6.0f;

    const float row1Top = titleBottom + equalGap;
    const float row2Top = row1Top + row1Metrics.height + equalGap;
    const float row3Top = row2Top + row2Metrics.height + equalGap;
    const float row4Top = row3Top + row3Metrics.height + equalGap;
    const float row5Top = row4Top + row4Metrics.height + equalGap;

    auto positionLeftRow = [&](sf::Text& labelText, sf::Text& valueText, 
                               float topY, float topOffset) {
        const sf::FloatRect labelBounds = labelText.getLocalBounds();
        const sf::FloatRect valueBounds = valueText.getLocalBounds();
        const float labelTop = textTopOffset(labelText);
        const float valueTop = textTopOffset(valueText);
        const float labelY = topY + (topOffset - labelTop);
        const float valueY = topY + (topOffset - valueTop);

        labelText.setPosition(leftEdge - labelBounds.left, labelY);
        valueText.setPosition(leftEdge + labelBounds.width + valueSpacing - valueBounds.left,
                              valueY);
    };

    auto positionRightRow = [&](sf::Text& labelText, sf::Text& valueText, 
                                float topY, float topOffset) {
        const sf::FloatRect labelBounds = labelText.getLocalBounds();
        const sf::FloatRect valueBounds = valueText.getLocalBounds();
        const float labelTop = textTopOffset(labelText);
        const float valueTop = textTopOffset(valueText);
        const float labelY = topY + (topOffset - labelTop);
        const float valueY = topY + (topOffset - valueTop);

        const float valueX = rightEdge - (valueBounds.width + valueBounds.left);
        valueText.setPosition(valueX, valueY);
        labelText.setPosition(valueX - valueSpacing - labelBounds.width - labelBounds.left,
                              labelY);
    };

    positionLeftRow(totalCustomersLabelText, totalCustomersValueText, row1Top, row1Metrics.topOffset);
    positionLeftRow(resigningCustomersLabelText, resigningCustomersValueText, row2Top, row2Metrics.topOffset);
    positionLeftRow(insideCustomersLabelText, insideCustomersValueText, row3Top, row3Metrics.topOffset);
    positionLeftRow(leavingCustomersLabelText, leavingCustomersValueText, row4Top, row4Metrics.topOffset);

    positionRightRow(orderedDishesLabelText, orderedDishesValueText, row1Top, row1Metrics.topOffset);
    positionRightRow(preparedDishesLabelText, preparedDishesValueText, row2Top, row2Metrics.topOffset);
    positionRightRow(servedDishesLabelText, servedDishesValueText, row3Top, row3Metrics.topOffset);
    positionRightRow(eatenDishesLabelText, eatenDishesValueText, row4Top, row4Metrics.topOffset);
    positionRightRow(droppedDishesLabelText, droppedDishesValueText, row5Top, row5Metrics.topOffset);
}

bool Summary::isMouseOverText(sf::RenderWindow* window, sf::Text text) {
    const sf::Vector2i mousePositions = sf::Mouse::getPosition(*window);
    const sf::Vector2f mouseWindowPositions = window->mapPixelToCoords(mousePositions);
    return text.getGlobalBounds().contains(mouseWindowPositions);
}

void Summary::updateHoverState(sf::RenderWindow* window) {
    const sf::Color normalReturnColor(255, 236, 141);
    const sf::Color hoverReturnColor(255, 255, 210);

    returnText.setFillColor(isMouseOverText(window, returnText) ? hoverReturnColor : 
                            normalReturnColor);
}

void Summary::handleMouseClick(sf::RenderWindow* window) {
    if(isMouseOverText(window, returnText)) {
        isSceneToChange = true;
    }
}

void Summary::drawBackgroundWithBlur(sf::RenderWindow* window) {
    const sf::Vector2u windowSize = window->getSize();
    const float downsampleFactor = 1.45f;
    const unsigned int reducedWidth = std::max(1u, static_cast<unsigned int>(
        std::round(static_cast<float>(windowSize.x) / downsampleFactor)));
    const unsigned int reducedHeight = std::max(1u, static_cast<unsigned int>(
        std::round(static_cast<float>(windowSize.y) / downsampleFactor)));

    if(blurTextureSize.x != reducedWidth || blurTextureSize.y != reducedHeight) {
        if(!blurRenderTexture.create(reducedWidth, reducedHeight)) {
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

void Summary::update(float deltaTime, sf::RenderWindow* window) {
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


bool Summary::changeScene(enum ScenesEnum* sceneName) {
    if(isSceneToChange) {
        *sceneName = ScenesEnum::MAIN_MENU;
        return true;
    }
    return false;
}

void Summary::render(sf::RenderWindow* window) {
    if(texturesLoaded) {
        drawBackgroundWithBlur(window);
    }

    if(fontLoaded) {
        window->draw(titleText);

        window->draw(totalCustomersLabelText);
        window->draw(totalCustomersValueText);
        window->draw(resigningCustomersLabelText);
        window->draw(resigningCustomersValueText);
        window->draw(insideCustomersLabelText);
        window->draw(insideCustomersValueText);
        window->draw(leavingCustomersLabelText);
        window->draw(leavingCustomersValueText);

        window->draw(orderedDishesLabelText);
        window->draw(orderedDishesValueText);
        window->draw(preparedDishesLabelText);
        window->draw(preparedDishesValueText);
        window->draw(servedDishesLabelText);
        window->draw(servedDishesValueText);
        window->draw(eatenDishesLabelText);
        window->draw(eatenDishesValueText);
        window->draw(droppedDishesLabelText);
        window->draw(droppedDishesValueText);

        window->draw(returnText);
    }
}