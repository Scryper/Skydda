#include "MenuScreen.h"

int MenuScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    position = getScreenCenter(&app);

    /// Load background image
    initBackground();

    /// Load buttons (clickable sprites)
    position.setY(position.getY() - 150);
    Position positionText(position.getX() - 75, position.getY() - 12);
    buttonChooseCharacters = initSprite(1.f, 1.f, PATH_BUTTON, position, &textureButton);
    // Text of buttonChooseCharacters
    positionText.setX(positionText.getX() + 40);
    textChooseCharacters = TextInitializer::createText(TEXT_PLAY, positionText);

    /// OptionScreen button
    position.setY(position.getY() + 100);
    buttonOptions = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonOptions
    positionText.setY(positionText.getY() + 100);
    positionText.setX(positionText.getX() - 35);
    textOptions = TextInitializer::createText(TEXT_OPTIONS, positionText);

    /// Quit button
    position.setY(position.getY() + 100);
    positionText.setY(positionText.getY() + 100);
    positionText.setX(positionText.getX() + 35);
    buttonQuit = initSprite(.5f, 1.f, position, &textureButton);
    // Text of buttonQuit
    textQuit = TextInitializer::createText(TEXT_QUIT, positionText);
    textQuit.setFillColor(TextInitializer::BetterRed);

    /// Font of texts
    initFonts();

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;
        }
        // Get the mouse position to verify if the user is over a sprite and/or click a sprite
        mousePosition = getMousePosition(&app);

        /// Button play
        if(buttonChooseCharacters.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) return 1; // ChooseCharacterScreen is in position 1 in screens (see main.cpp)
            else { // The user sees that he is over a text
                textChooseCharacters.setFillColor(sf::Color::Green);
            }
        }
        else { // The text stays white if the user doesn't go over it, or come back to white if the user is no longer over it
            textChooseCharacters.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button options
        if(buttonOptions.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) return 2;
            else {
                textOptions.setFillColor(sf::Color::Green);
            }
        }
        else {
            textOptions.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button quit
        if(buttonQuit.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) return -1;
            else {
                textQuit.setFillColor(TextInitializer::DarkerBetterRed);
            }
        }
        else {
            textQuit.setFillColor(TextInitializer::BetterRed);
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

void MenuScreen::initBackground() {
    background = initSprite(1.f, 1.f, PATH_BACKGROUND, position, &textureBackground);
}

// load the font on the texts
void MenuScreen::initFonts() {
    font.loadFromFile(PATH_FONT);

    texts.push_back(&textChooseCharacters);
    texts.push_back(&textOptions);
    texts.push_back(&textQuit);

    TextInitializer::initFont(texts, &font);
}
