#include "MenuScreen.h"

int MenuScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    Position position(middleScreenX, middleScreenY);
    Position positionText(middleScreenX-75, middleScreenY-12);


    /// Load background image
    sf::Texture textureBackground;
    sf::Sprite background = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    /// Load buttons (clickable sprites)
    /// GameScreen Button !!!!TMP -> need intermediate GUI
    sf::Texture textureButton; // Button texture
    sf::Sprite buttonChooseCharacters = initSprite(1.f, 1.f, "resources/images/button/button.png", position, &textureButton);
    // Text of buttonChooseCharacters
    sf::Text textChooseCharacters = TextInitializer::createText("Play", positionText);

    /// OptionScreen button
    position.setY(position.getY() + 100);
    positionText.setY(positionText.getY() + 100);
    sf::Sprite buttonOptions = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonOptions
    sf::Text textOptions = TextInitializer::createText("Options", positionText);

    /// Quit button
    position.setY(position.getY() + 100);
    positionText.setY(positionText.getY() + 100);
    sf::Sprite buttonQuit = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonQuit
    sf::Text textQuit = TextInitializer::createText("Quit", positionText);
    textQuit.setFillColor(TextInitializer::betterRed);

    /// Font of texts
    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    textChooseCharacters.setFont(font);
    textOptions.setFont(font);
    textQuit.setFont(font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        // Get the mouse position to verify if the user is over a sprite and/or click a sprite
        sf::Vector2i mousePosition = sf::Mouse::getPosition(app);
        sf::Vector2f adaptedPosition = app.mapPixelToCoords(mousePosition);

        /// Button play
        if(buttonChooseCharacters.getGlobalBounds().contains(adaptedPosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 1; // GameScreen is in position 1 in screens (see main.cpp)
            }
            else { // The user sees that he is over a text
                textChooseCharacters.setFillColor(sf::Color::Green);
            }
        }
        else { // The text stays white if the user doesn't go over it, or come back to white if the user is no longer over it
            textChooseCharacters.setFillColor(TextInitializer::betterWhite);
        }

        /// Button options
        if(buttonOptions.getGlobalBounds().contains(adaptedPosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 2;
            }
            else {
                textOptions.setFillColor(sf::Color::Green);
            }
        }
        else {
            textOptions.setFillColor(TextInitializer::betterWhite);
        }

        /// Button quit
        if(buttonQuit.getGlobalBounds().contains(adaptedPosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return -1;
            }
            else {
                textQuit.setFillColor(TextInitializer::darkerBetterRed);
            }
        }
        else {
            textQuit.setFillColor(TextInitializer::betterRed);
        }

        app.clear();

        /// Draw elements
        app.draw(background);

        app.draw(buttonChooseCharacters);
        app.draw(textChooseCharacters);

        app.draw(buttonOptions);
        app.draw(textOptions);

        app.draw(buttonQuit);
        app.draw(textQuit);

        app.display();
    }

    return -1; // Never reach, but in case
}
