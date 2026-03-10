#include "Scene.h"

class MainMenu : public Scene {
private:
    float timeElapsed = 0.0f;
public:
    void update(sf::RenderWindow& window, float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};