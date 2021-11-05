#include "ChooseCharacterScreen.h"

int ChooseCharacterScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    sf::Vector2f mousePosition;

    Position position = getScreenCenter(&app);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    sf::String input;
    sf::Texture textureButton; // Button texture
    /// First player elements
    Position playerElements(350, 200);
    sf::Text firstPlayerName = TextInitializer::createText("Player 1", playerElements);

    playerElements.setX(playerElements.getX() + 100);
    playerElements.setY(playerElements.getY() + 700);
    sf::Sprite buttonValidateFirstPlayer = initSprite(1.f, 1.f, "resources/images/button/button.png", playerElements, &textureButton);

    playerElements.setX(playerElements.getX() - 60);
    playerElements.setY(playerElements.getY() - 12);
    sf::Text textValidateFirstPlayer = TextInitializer::createText("Validate", playerElements);

    /// Second player elements
    //Reset
    playerElements.setX(playerElements.getX() + 60);
    playerElements.setY(playerElements.getY() + 12);
    playerElements.setX(position.getX() * 2 - 450);
    playerElements.setY(playerElements.getY() - 700);

    sf::Text secondPlayerName = TextInitializer::createText("Player 2", playerElements);

    playerElements.setX(playerElements.getX() + 50);
    playerElements.setY(playerElements.getY() + 700);
    sf::Sprite buttonValidateSecondPlayer = initSprite(1.f, 1.f, playerElements, &textureButton);

    playerElements.setX(playerElements.getX() - 60);
    playerElements.setY(playerElements.getY() - 12);
    sf::Text textValidateSecondPlayer = TextInitializer::createText("Validate", playerElements);

    /// Load buttons (clickable sprites)
    position.setY(position.getY() + 300);
    Position positionButtonText(position.getX() - 75, position.getY() - 12);

    sf::Sprite buttonPlay = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonChooseCharacters
    positionButtonText.setX(positionButtonText.getX() + 40);
    sf::Text textPlay = TextInitializer::createText("Play", positionButtonText);
    textPlay.setFillColor(TextInitializer::BetterGrey);

    /// Back button
    position.setY(position.getY() + 100);
    sf::Sprite buttonBack = initSprite(.5f, 1.f, position, &textureButton);
    // Text of buttonQuit
    positionButtonText.setY(positionButtonText.getY() + 100);
    sf::Text textBack = TextInitializer::createText("Back", positionButtonText);
    textBack.setFillColor(TextInitializer::BetterRed);

    /// Font of texts
    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    textPlay.setFont(font);
    textBack.setFont(font);

    firstPlayerName.setFont(font);
    textValidateFirstPlayer.setFont(font);

    secondPlayerName.setFont(font);
    textValidateSecondPlayer.setFont(font);

    bool firstPlayerOk = false;
    bool secondPlayerOk = false;
    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }

            if(event.type == sf::Event::TextEntered) {
                if(!firstPlayerOk) { // change first player name

                }
                else { // change second player name

                }
                input += event.text.unicode;
                textBack.setString(input);
            }
        }

        mousePosition = getMousePosition(&app);

        /// Button play
        if(buttonPlay.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 2;
            }
            else if(firstPlayerOk && secondPlayerOk) {
                textPlay.setFillColor(sf::Color::Green);
            }
        }
        else if(!firstPlayerOk || !secondPlayerOk) {
            textPlay.setFillColor(TextInitializer::BetterGrey);
        }
        else {
            textPlay.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button back
        if(buttonBack.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                return 0;
            }
            else {
                textBack.setFillColor(TextInitializer::DarkerBetterRed);
            }
        }
        else {
            textBack.setFillColor(TextInitializer::BetterRed);
        }

        app.clear();

        /// Draw elements
        app.draw(backgroundSprite);

        app.draw(buttonPlay);
        app.draw(textPlay);

        app.draw(buttonBack);
        app.draw(textBack);

        // First player elements
        app.draw(firstPlayerName);
        app.draw(buttonValidateFirstPlayer);
        app.draw(textValidateFirstPlayer);

        // Second player elements
        app.draw(secondPlayerName);
        app.draw(buttonValidateSecondPlayer);
        app.draw(textValidateSecondPlayer);

        app.display();
    }

    return -1;
}
