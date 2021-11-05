#include "OptionScreen.h"

int OptionScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    sf::Vector2f mousePosition;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    Position position(middleScreenX, middleScreenY);
    Position positionText(middleScreenX - 75, middleScreenY - 12);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    sf::Texture textureButton;
    sf::Sprite buttonBack = initSprite(1.f, 1.f, "resources/images/button/button.png", position, &textureButton);
    // Text of buttonQuit
    sf::Text textBack = TextInitializer::createText("Back", position);
    textBack.setFillColor(TextInitializer::betterRed);

    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    textBack.setFont(font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        // Get the mouse position to verify if the user is over a sprite and/or click a sprite
        mousePosition = getMousePosition(&app);

        /// Button quit
        if(buttonBack.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 0;
            }
            else {
                textBack.setFillColor(TextInitializer::darkerBetterRed);
            }
        }
        else {
            textBack.setFillColor(TextInitializer::betterRed);
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);

        app.draw(buttonBack);
        app.draw(textBack);

        app.display();
    }

    return -1;
}
