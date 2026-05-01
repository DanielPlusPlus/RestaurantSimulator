#include "scenes/Level.hpp"

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>


Level::Level(int scaleFactor, int chefsNumber, int waitersNumber, 
             int twoChairsTablesNumber, int fourChairsTablesNumber, 
             int timeToEndSimulationInMinutes, 
             int* totalCustomersNumberCounterPtr,
             int* resigningCustomersNumberCounterPtr,
             int* insideCustomersNumberCounterPtr,
             int* leavingCustomersNumberCounterPtr,
             int* orderedDishesNumberCounterPtr,
             int* preparedDishesNumberCounterPtr,
             int* servedDishesNumberCounterPtr,
             int* eatenDishesNumberCounterPtr,
             int* droppedDishesNumberCounterPtr
            ) : Scene(scaleFactor),
                timeToEndSimulationInMinutes(timeToEndSimulationInMinutes),
                totalCustomersNumberCounterPtr(totalCustomersNumberCounterPtr),
                resigningCustomersNumberCounterPtr(resigningCustomersNumberCounterPtr),
                insideCustomersNumberCounterPtr(insideCustomersNumberCounterPtr),
                leavingCustomersNumberCounterPtr(leavingCustomersNumberCounterPtr),
                orderedDishesNumberCounterPtr(orderedDishesNumberCounterPtr),
                preparedDishesNumberCounterPtr(preparedDishesNumberCounterPtr),
                servedDishesNumberCounterPtr(servedDishesNumberCounterPtr),
                eatenDishesNumberCounterPtr(eatenDishesNumberCounterPtr),
                droppedDishesNumberCounterPtr(droppedDishesNumberCounterPtr) {
    tileWidth *= scaleFactor;
    tileHeight *= scaleFactor;
    dishesManager = new DishesManager(scaleFactor);
    tablesManager = new TablesManager(scaleFactor, twoChairsTablesNumber, fourChairsTablesNumber);
    charactersManager = new CharactersManager(scaleFactor, tileWidth, tileHeight, 
                                              chefsNumber, waitersNumber, dishesManager);
    pathFinder = new PathFinder(this);
    this->texturesLoaded = loadTextures(scaleFactor);
    if(fontLoaded) {
        configureTextsStyles();
        updateValuesTexts();
    }
}

Level::~Level() {
    charactersManager->getStatistics(totalCustomersNumberCounterPtr, resigningCustomersNumberCounterPtr, 
                                     insideCustomersNumberCounterPtr, leavingCustomersNumberCounterPtr, 
                                     orderedDishesNumberCounterPtr, preparedDishesNumberCounterPtr, 
                                     servedDishesNumberCounterPtr, eatenDishesNumberCounterPtr, 
                                     droppedDishesNumberCounterPtr);
    delete dishesManager;
    delete tablesManager;
    delete charactersManager;
    delete pathFinder;
}

bool Level::loadTextures(int scaleFactor) {
    if(!backgroundTexture.loadFromFile("assets/interiors/background.png")) {
        return false;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if(!kitchenWallsTexture.loadFromFile("assets/interiors/kitchen_walls.png")) {
        return false;
    }
    kitchenWallsSprite.setTexture(kitchenWallsTexture);
    kitchenWallsSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if(!entranceWallsTexture.loadFromFile("assets/interiors/entrance_walls.png")) {
        return false;
    }
    entranceWallsSprite.setTexture(entranceWallsTexture);
    entranceWallsSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if(!flowersTexture.loadFromFile("assets/interiors/flowers.png")) {
        return false;
    }
    flowersSprite.setTexture(flowersTexture);
    flowersSprite.setScale(static_cast<float>(scaleFactor), static_cast<float>(scaleFactor));

    if(!font.loadFromFile("assets/fonts/determination.ttf")) {
        return false;
    }
    fontLoaded = true;

    return true;
}

void Level::configureTextsStyles() {
    const sf::Color labelColor(245, 233, 190);
    const sf::Color valueColor(255, 222, 120);
    const sf::Color outlineColor(58, 58, 80);

    timeLabelText.setFont(font);
    timeLabelText.setCharacterSize(fontSize * scaleFactor);
    timeLabelText.setString("Remaining Time:");
    timeLabelText.setFillColor(labelColor);
    timeLabelText.setOutlineThickness(0.8f * static_cast<float>(scaleFactor));
    timeLabelText.setOutlineColor(outlineColor);

    timeValueText.setFont(font);
    timeValueText.setCharacterSize(fontSize * scaleFactor);
    timeValueText.setFillColor(valueColor);
    timeValueText.setOutlineThickness(0.8f * static_cast<float>(scaleFactor));
    timeValueText.setOutlineColor(outlineColor);

    speedMultiplierLabelText.setFont(font);
    speedMultiplierLabelText.setCharacterSize(fontSize * scaleFactor);
    speedMultiplierLabelText.setString("Speed Multiplier:");
    speedMultiplierLabelText.setFillColor(labelColor);
    speedMultiplierLabelText.setOutlineThickness(0.8f * static_cast<float>(scaleFactor));
    speedMultiplierLabelText.setOutlineColor(outlineColor);

    speedMultiplierValueText.setFont(font);
    speedMultiplierValueText.setCharacterSize(fontSize * scaleFactor);
    speedMultiplierValueText.setFillColor(valueColor);
    speedMultiplierValueText.setOutlineThickness(0.8f * static_cast<float>(scaleFactor));
    speedMultiplierValueText.setOutlineColor(outlineColor);
}

void Level::updateValuesTexts() {
    int minutes = std::max(0, minutesNumber);
    int seconds = std::max(0, secondsNumber % 60);
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    timeValueText.setString(oss.str());

    speedMultiplierValueText.setString(std::string("x") + std::to_string(speedMultiplier));
}

void Level::updateTextsPositions() {
    const float margin = 8.0f * static_cast<float>(scaleFactor);

    const sf::FloatRect timeLabelBounds = timeLabelText.getLocalBounds();
    timeLabelText.setPosition(margin - timeLabelBounds.left, margin - timeLabelBounds.top);

    const sf::FloatRect timeValueBounds = timeValueText.getLocalBounds();
    timeValueText.setPosition(margin + timeLabelBounds.width + 6.0f * scaleFactor - timeValueBounds.left,
                              margin - timeValueBounds.top);
    
    const float rightEdge = static_cast<float>(302 * scaleFactor) - margin;
    const sf::FloatRect labelBounds = speedMultiplierLabelText.getLocalBounds();
    const sf::FloatRect valueBounds = speedMultiplierValueText.getLocalBounds();
    const float spacing = 6.0f * static_cast<float>(scaleFactor);
    const float totalWidth = labelBounds.width + spacing + valueBounds.width;
    const float leftX = rightEdge - totalWidth;

    speedMultiplierLabelText.setPosition(leftX - labelBounds.left, margin - labelBounds.top);
    speedMultiplierValueText.setPosition(leftX + labelBounds.width + spacing - valueBounds.left,
                                         margin - valueBounds.top);
}

bool Level::isMouseOverText(sf::RenderWindow* window, sf::Text text) {
    const sf::Vector2i mousePositions = sf::Mouse::getPosition(*window);
    const sf::Vector2f mouseWindowPositions = window->mapPixelToCoords(mousePositions);
    return text.getGlobalBounds().contains(mouseWindowPositions);
}

void Level::updateHoverState(sf::RenderWindow* window) {
    const sf::Color normalValueColor(255, 222, 120);
    const sf::Color hoverValueColor(255, 255, 190);

    speedMultiplierValueText.setFillColor(isMouseOverText(window, speedMultiplierValueText) ?
                                         hoverValueColor : normalValueColor);
}

void Level::handleMouseClick(sf::RenderWindow* window, bool isLeftClick) {
    int value = isLeftClick ? 1 : -1;
    if(isMouseOverText(window, speedMultiplierValueText)) {
        speedMultiplier = std::max(1, std::min(speedMultiplier + value, 60));
        updateValuesTexts();
    }
}

void Level::update(float deltaTime, sf::RenderWindow* window) {
    (void)window;
    sf::Event event;
    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window->close();
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(window, true);
            }
            else if(event.mouseButton.button == sf::Mouse::Right) {
                handleMouseClick(window, false);
            }
        }
    }

    deltaTime *= speedMultiplier;

    this->charactersManager->update(deltaTime, scaleFactor, 
                                    tileWidth, tileHeight, 
                                    dishesManager, tablesManager, 
                                    pathFinder);
    simulationTime += deltaTime;

    float remainingTimeInMinutes = timeToEndSimulationInMinutes - (simulationTime / 60.0f);
    remainingTimeInMinutes = std::max(0.0f, remainingTimeInMinutes);

    minutesNumber = static_cast<int>(remainingTimeInMinutes);
    secondsNumber = static_cast<int>((remainingTimeInMinutes - minutesNumber) * 60);

    if(remainingTimeInMinutes <= 0) {
        isSceneToChange = true;
    }
    updateValuesTexts();
    updateTextsPositions();
    updateHoverState(window);
}

bool Level::changeScene(enum ScenesEnum* sceneName) {
    if(isSceneToChange) {
        *sceneName = ScenesEnum::SUMMARY;
        return true;
    }
    return false;
}

void Level::render(sf::RenderWindow* window) {
    if(texturesLoaded) {
        window->draw(backgroundSprite);
        window->draw(flowersSprite);
        this->charactersManager->renderChefs(window);
        window->draw(kitchenWallsSprite);
        this->dishesManager->renderReadyDish(window);

        enum class RenderType {
            Table,
            Dish,
            Character
        };

        struct RenderItem {
            float sortY = 0.0f;
            RenderType type = RenderType::Table;
            void* ptr = nullptr;
        };

        std::vector<RenderItem> renderItems;
        const std::vector<Table*> tables = tablesManager->getTables();
        const std::vector<Character*> characters = charactersManager->getWaitersAndInsideCustomers();
        const std::vector<Dish*>& dishes = dishesManager->getDishesOnTables();

        renderItems.reserve(tables.size() + characters.size() + dishes.size());
        for(Table* table : tables) {
            renderItems.push_back(RenderItem{table->getSortY() * static_cast<float>(scaleFactor),
                                             RenderType::Table, table});
        }
        for(Dish* dish : dishes) {
            renderItems.push_back(RenderItem{dish->getYPos(), RenderType::Dish, dish});
        }
        for(Character* character : characters) {
            renderItems.push_back(RenderItem{character->getSortY(), RenderType::Character, character});
        }

        std::stable_sort(renderItems.begin(), renderItems.end(),
                         [](const RenderItem& left, const RenderItem& right) {
                             return left.sortY < right.sortY;
                         });

        for(const RenderItem& item : renderItems) {
            if(item.type == RenderType::Table) {
                static_cast<Table*>(item.ptr)->render(window);
            }
            else if(item.type == RenderType::Dish) {
                static_cast<Dish*>(item.ptr)->render(window);
            }
            else {
                static_cast<Character*>(item.ptr)->render(window);
            }
        }
        window->draw(entranceWallsSprite);
        this->charactersManager->renderWaitingResigningInsideLeavingCustomers(window);
       
    }

    if(fontLoaded) {
        window->draw(timeLabelText);
        window->draw(timeValueText);
        window->draw(speedMultiplierLabelText);
        window->draw(speedMultiplierValueText);
    }
}

bool Level::isValidPositions(Positions positions) {
    if(positions.xPos >= (151.0f * scaleFactor) && 
      positions.xPos <= (280.0f * scaleFactor) && 
      positions.yPos == (24.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (24.0f * scaleFactor) 
       && positions.yPos <= (56.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (24.0f * scaleFactor) 
       && positions.yPos <= (56.0f * scaleFactor)) {
        return true;
    }
     if(positions.xPos >= (70.0f * scaleFactor) 
         && positions.xPos <= (88.0f * scaleFactor)
         && positions.yPos == (72.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos > (151.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor)
       && positions.yPos == (64.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor)
       && positions.yPos > (56.0f * scaleFactor)
       && positions.yPos <= (72.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor)
       && positions.yPos == (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (70.0f * scaleFactor) 
       && positions.xPos <= (88.0f * scaleFactor)
       && positions.yPos > (72.0f * scaleFactor)
       && positions.yPos <= (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (151.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (72.0f * scaleFactor)
       && positions.yPos <= (88.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor) 
       && positions.yPos == (104.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (88.0f * scaleFactor)
       && positions.yPos <= (104.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos == (112.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (52.0f * scaleFactor) 
       && positions.xPos <= (212.0f * scaleFactor) 
       && positions.yPos > (104.0f * scaleFactor)
       && positions.yPos <= (112.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (101.0f * scaleFactor) 
       && positions.xPos <= (164.0f * scaleFactor)
       && positions.yPos > (120.0f * scaleFactor)
       && positions.yPos <= (136.0f * scaleFactor)) { 
        return true;
    }
    if(positions.xPos >= (7.0f * scaleFactor) 
       && positions.xPos <= (280.0f * scaleFactor) 
       && positions.yPos == (152.0f * scaleFactor)) {
        return true;
    }
    if(positions.xPos >= (101.0f * scaleFactor) 
       && positions.xPos <= (164.0f * scaleFactor)
       && positions.yPos > (136.0f * scaleFactor)
       && positions.yPos <= (152.0f * scaleFactor)) { 
        return true;
    }
    if(positions.xPos >= (131.0f * scaleFactor) 
       && positions.xPos <= (171.0f * scaleFactor)
       && positions.yPos > (152.0f * scaleFactor) 
       && positions.yPos <= (168.0f * scaleFactor)) {
        return true;
    }
    return false;
}