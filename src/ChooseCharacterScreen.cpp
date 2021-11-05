#include "ChooseCharacterScreen.h"

int ChooseCharacterScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    sf::Vector2f mousePosition;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    Position position(middleScreenX, middleScreenY);
    Position positionText(middleScreenX - 75, middleScreenY - 12);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    /// Load buttons (clickable sprites)
    sf::Texture textureButton; // Button texture
    sf::Sprite buttonPlay = initSprite(1.f, 1.f, "resources/images/button/button.png", position, &textureButton);
    // Text of buttonChooseCharacters
    sf::Text textPlay = TextInitializer::createText("Play", positionText);

    /// Back button
    position.setY(position.getY() + 100);
    positionText.setY(positionText.getY() + 100);
    sf::Sprite buttonBack = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonQuit
    sf::Text textBack = TextInitializer::createText("Back", positionText);
    textBack.setFillColor(TextInitializer::betterRed);

    /// Font of texts
    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    textPlay.setFont(font);
    textBack.setFont(font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        mousePosition = getMousePosition(&app);

        /// Button back
        if(buttonPlay.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 2;
            }
            else {
                textPlay.setFillColor(sf::Color::Green);
            }
        }
        else {
            textPlay.setFillColor(TextInitializer::betterWhite);
        }

        /// Button back
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

        app.draw(buttonPlay);
        app.draw(textPlay);

        app.draw(buttonBack);
        app.draw(textBack);

        app.display();
    }

    return -1;
}
