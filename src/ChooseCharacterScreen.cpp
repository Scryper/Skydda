#include "ChooseCharacterScreen.h"

int ChooseCharacterScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    int indexMap = 0;
    std::vector<std::string> maps;
    maps.push_back("resources/images/visuals/map1_visual.png");
    maps.push_back("resources/images/visuals/map2_visual.png");

    sf::Event event;

    sf::Vector2f mousePosition;

    Position position = getScreenCenter(&app);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(.45f, .45f, "resources/images/background/background_choose.png", position, &textureBackground);

    sf::String input;
    sf::Texture textureButton; // Button texture
    /// First player elements
    Position playerElements(250, 200);
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
    playerElements.setX(position.getX() * 2 - 350);
    playerElements.setY(playerElements.getY() - 700);

    sf::Text secondPlayerName = TextInitializer::createText("Player 2", playerElements);

    playerElements.setX(playerElements.getX() + 50);
    playerElements.setY(playerElements.getY() + 700);
    sf::Sprite buttonValidateSecondPlayer = initSprite(1.f, 1.f, playerElements, &textureButton);

    playerElements.setX(playerElements.getX() - 60);
    playerElements.setY(playerElements.getY() - 12);
    sf::Text textValidateSecondPlayer = TextInitializer::createText("Validate", playerElements);
    textValidateSecondPlayer.setFillColor(TextInitializer::BetterGrey);

    /// Map elements
    Position positionMap(position.getX(), 500);

    sf::Texture textureMap;
    sf::Sprite spriteMap = initSprite(.2f, .2f, maps[indexMap], positionMap, &textureMap);

    auto scaledWidth = textureMap.getSize().x * spriteMap.getScale().x;
    auto scaledHeight = textureMap.getSize().y * spriteMap.getScale().y;

    sf::RectangleShape outlineMap(sf::Vector2f(scaledWidth + 10, scaledHeight + 10));
    outlineMap.setPosition(positionMap.getX() - (scaledWidth / 2) - 5, positionMap.getY() - (scaledHeight / 2) - 5);

    Position positionButtonsMap(860, 700);
    Position positionTextMap(positionButtonsMap.getX() - 75, positionButtonsMap.getY() - 13);

    sf::Sprite buttonPreviousMap = initSprite(.7f, 1.f, positionButtonsMap, &textureButton);
    sf::Text textPreviousMap = TextInitializer::createText("Previous", positionTextMap);

    positionButtonsMap.setX(positionButtonsMap.getX() + 200);
    positionTextMap.setX(positionTextMap.getX() + 240);
    sf::Sprite buttonNextMap = initSprite(.7f, 1.f, positionButtonsMap, &textureButton);
    sf::Text textNextMap = TextInitializer::createText("Next", positionTextMap);

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

    std::vector<sf::Text*> texts;
    texts.push_back(&textPlay);
    texts.push_back(&textBack);
    texts.push_back(&firstPlayerName);
    texts.push_back(&textValidateFirstPlayer);
    texts.push_back(&secondPlayerName);
    texts.push_back(&textValidateSecondPlayer);
    texts.push_back(&textNextMap);
    texts.push_back(&textPreviousMap);

    TextInitializer::initFont(texts, &font);

    bool firstPlayerOk = false;
    bool secondPlayerOk = false;
    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }

            if(event.type == sf::Event::TextEntered) {
                if(!firstPlayerOk) { // change first player name
                    if(input.getSize() < 10) {
                        input += event.text.unicode;
                        firstPlayerName.setString(input);
                    }
                }
                else { // change second player name
                    if(input.getSize() < 10) {
                        input += event.text.unicode;
                        secondPlayerName.setString(input);
                    }
                }
            }
        }

        mousePosition = getMousePosition(&app);

        /// Button play
        if(buttonPlay.getGlobalBounds().contains(mousePosition)) {
            if(firstPlayerOk && secondPlayerOk) {
                textPlay.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    map_ = indexMap + 1;
                    return 2;
                }
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

        /// Next map
        if(buttonNextMap.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                if(indexMap < (int)(maps.size() - 1)) {
                    indexMap++;
                    textureMap.loadFromFile(maps[indexMap]);
                    spriteMap.setTexture(textureMap, true);
                }
            }
            else {
                textNextMap.setFillColor(sf::Color::Green);
            }
        }
        else {
            textNextMap.setFillColor(TextInitializer::BetterWhite);
        }

        /// Previous map
        if(buttonPreviousMap.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                if(indexMap > 0) {
                    indexMap--;
                    textureMap.loadFromFile(maps[indexMap]);
                    spriteMap.setTexture(textureMap, true);
                }
            }
            else {
                textPreviousMap.setFillColor(sf::Color::Green);
            }
        }
        else {
            textPreviousMap.setFillColor(TextInitializer::BetterWhite);
        }

        /// First player
        if(!firstPlayerOk) {
            if(buttonValidateFirstPlayer.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    firstPlayerOk = true;
                    textValidateFirstPlayer.setString("Validated");
                    textValidateFirstPlayer.setPosition(textValidateFirstPlayer.getPosition().x - 10, textValidateFirstPlayer.getPosition().y);
                    strFirstPlayerName = firstPlayerName.getString().toAnsiString();

                    // Preparing for second player
                    textValidateSecondPlayer.setFillColor(TextInitializer::BetterWhite);
                    input = "";
                }
                else {
                    textValidateFirstPlayer.setFillColor(sf::Color::Green);
                }
            }
            else {
                textValidateFirstPlayer.setFillColor(TextInitializer::BetterWhite);
            }
        }

        /// Second Player
        if(firstPlayerOk && !secondPlayerOk) {
            if(buttonValidateSecondPlayer.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    secondPlayerOk = true;
                    textValidateSecondPlayer.setString("Validated");
                    textValidateSecondPlayer.setPosition(textValidateSecondPlayer.getPosition().x - 10, textValidateSecondPlayer.getPosition().y);
                    strSecondPlayerName = secondPlayerName.getString().toAnsiString();
                }
                else {
                    textValidateSecondPlayer.setFillColor(sf::Color::Green);
                }
            }
            else {
                textValidateSecondPlayer.setFillColor(TextInitializer::BetterWhite);
            }
        }

        app.clear();

        /// Draw elements
        app.draw(backgroundSprite);

        app.draw(buttonPlay);
        app.draw(textPlay);

        app.draw(buttonBack);
        app.draw(textBack);

        // Map elements
        app.draw(outlineMap);
        app.draw(spriteMap);

        app.draw(buttonPreviousMap);
        app.draw(textPreviousMap);

        app.draw(buttonNextMap);
        app.draw(textNextMap);

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
