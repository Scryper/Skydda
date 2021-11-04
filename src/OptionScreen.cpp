#include "OptionScreen.h"

int OptionScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    Position position(middleScreenX, middleScreenY);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    sf::Texture textureButton;
    sf::Sprite buttonQuit = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonQuit
    sf::Text textQuit = TextInitializer::createText("Quit", position);
    textQuit.setFillColor(TextInitializer::betterRed);

    sf::Font font;
    font.loadFromFile("resources/fonts/arial.ttf");

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);

        app.display();
    }

    return -1;
}
