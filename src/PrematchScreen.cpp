#include "PrematchScreen.h"

int PrematchScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    position = getScreenCenter(&app);

    initVectors();
    initBackground();
    initPositions();

    /// First player elements
    // Name
    firstPlayerName = TextInitializer::createText("Dark Golem", positionPlayerElements);

    // Show selected character
    positionPlayerElements.setX(positionPlayerElements.getX() + 100);
    positionPlayerElements.setY(positionPlayerElements.getY() + 300);
    spriteCharacter1 = initSprite(1.f, 1.f, characters[indexCharacter], positionPlayerElements, &textureCharacter1);

    // Buttons to choose the charater
    // Previous
    positionPlayerElements.setX(positionPlayerElements.getX() - 150);
    positionPlayerElements.setY(positionPlayerElements.getY() + 200);
    buttonFirstPlayerPrevious = initSprite(.7f, 1.f, "resources/images/buttons/button.png", positionPlayerElements, &textureButton);

    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    positionPlayerElements.setX(positionPlayerElements.getX() - 70);
    textFirstPlayerPrevious = TextInitializer::createText("Previous", positionPlayerElements);

    // Next
    positionPlayerElements.setY(positionPlayerElements.getY() + 12);
    positionPlayerElements.setX(positionPlayerElements.getX() + 270);
    buttonFirstPlayerNext = initSprite(.7f, 1.f, positionPlayerElements, &textureButton);
    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    positionPlayerElements.setX(positionPlayerElements.getX() - 40);
    textFirstPlayerNext = TextInitializer::createText("Next", positionPlayerElements);

    // Validate
    positionPlayerElements.setX(positionPlayerElements.getX() - 60);
    positionPlayerElements.setY(positionPlayerElements.getY() + 212);
    sf::Sprite buttonValidateFirstPlayer = initSprite(1.f, 1.f, positionPlayerElements, &textureButton);

    positionPlayerElements.setX(positionPlayerElements.getX() - 60);
    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    textValidateFirstPlayer = TextInitializer::createText("Validate", positionPlayerElements);

    /// Second player elements
    //Reset
    positionPlayerElements.setX(positionPlayerElements.getX() + 60);
    positionPlayerElements.setY(positionPlayerElements.getY() + 12);
    positionPlayerElements.setX(position.getX() * 2 - 500);
    positionPlayerElements.setY(positionPlayerElements.getY() - 700);

    // Name
    positionPlayerElements.setX(positionPlayerElements.getX() + 50);
    secondPlayerName = TextInitializer::createText("Light Golem", positionPlayerElements);

    // Show selected character
    positionPlayerElements.setX(positionPlayerElements.getX() + 100);
    positionPlayerElements.setY(positionPlayerElements.getY() + 300);
    spriteCharacter2 = initSprite(1.f, 1.f, characters[indexCharacter + 3], positionPlayerElements, &textureCharacter2);

    // Buttons to choose the charater
    // Previous
    positionPlayerElements.setX(positionPlayerElements.getX() - 100);
    positionPlayerElements.setY(positionPlayerElements.getY() + 200);
    buttonSecondPlayerPrevious = initSprite(.7f, 1.f, positionPlayerElements, &textureButton);

    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    positionPlayerElements.setX(positionPlayerElements.getX() - 70);
    textSecondPlayerPrevious = TextInitializer::createText("Previous", positionPlayerElements);
    textSecondPlayerPrevious.setFillColor(TextInitializer::BetterGrey);

    // Next
    positionPlayerElements.setY(positionPlayerElements.getY() + 12);
    positionPlayerElements.setX(positionPlayerElements.getX() + 270);
    buttonSecondPlayerNext = initSprite(.7f, 1.f, positionPlayerElements, &textureButton);

    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    positionPlayerElements.setX(positionPlayerElements.getX() - 40);
    textSecondPlayerNext = TextInitializer::createText("Next", positionPlayerElements);
    textSecondPlayerNext.setFillColor(TextInitializer::BetterGrey);

    // Validate
    positionPlayerElements.setX(positionPlayerElements.getX() - 60);
    positionPlayerElements.setY(positionPlayerElements.getY() + 212);
    buttonValidateSecondPlayer = initSprite(1.f, 1.f, positionPlayerElements, &textureButton);

    positionPlayerElements.setX(positionPlayerElements.getX() - 60);
    positionPlayerElements.setY(positionPlayerElements.getY() - 12);
    textValidateSecondPlayer = TextInitializer::createText("Validate", positionPlayerElements);
    textValidateSecondPlayer.setFillColor(TextInitializer::BetterGrey);

    /// Map elements
    Position positionMap(position.getX(), 500);

    spriteMap = initSprite(.2f, .2f, maps[indexMap], positionMap, &textureMap);

    auto scaledWidth = textureMap.getSize().x * spriteMap.getScale().x;
    auto scaledHeight = textureMap.getSize().y * spriteMap.getScale().y;

    sf::RectangleShape outlineMap(sf::Vector2f(scaledWidth + 10, scaledHeight + 10));
    outlineMap.setPosition(positionMap.getX() - (scaledWidth / 2) - 5, positionMap.getY() - (scaledHeight / 2) - 5);

    buttonPreviousMap = initSprite(.7f, 1.f, positionButtonsMap, &textureButton);
    textPreviousMap = TextInitializer::createText("Previous", positionTextMap);

    positionButtonsMap.setX(positionButtonsMap.getX() + 200);
    positionTextMap.setX(positionTextMap.getX() + 240);
    buttonNextMap = initSprite(.7f, 1.f, positionButtonsMap, &textureButton);
    textNextMap = TextInitializer::createText("Next", positionTextMap);

    /// Load buttons (clickable sprites)
    position.setY(position.getY() + 300);
    Position positionButtonText(position.getX() - 75, position.getY() - 12);

    buttonPlay = initSprite(1.f, 1.f, position, &textureButton);
    // Text of buttonChooseCharacters
    positionButtonText.setX(positionButtonText.getX() + 40);
    textPlay = TextInitializer::createText("Play", positionButtonText);
    textPlay.setFillColor(TextInitializer::BetterGrey);

    /// Back button
    position.setY(position.getY() + 100);
    buttonBack = initSprite(.5f, 1.f, position, &textureButton);
    // Text of buttonQuit
    positionButtonText.setY(positionButtonText.getY() + 100);
    textBack = TextInitializer::createText("Back", positionButtonText);
    textBack.setFillColor(TextInitializer::BetterRed);

    /// Font of texts
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
    texts.push_back(&textFirstPlayerNext);
    texts.push_back(&textFirstPlayerPrevious);
    texts.push_back(&textSecondPlayerNext);
    texts.push_back(&textSecondPlayerPrevious);

    TextInitializer::initFont(texts, &font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
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

            if(!firstPlayerOk) {
                // Previous character
                if(buttonFirstPlayerPrevious.getGlobalBounds().contains(mousePosition)) {
                    if(event.type == sf::Event::MouseButtonPressed) {
                        if(indexCharacter > 0) {
                            indexCharacter--;
                            textureCharacter1.loadFromFile(characters[indexCharacter]);
                            spriteCharacter1.setTexture(textureCharacter1, true);
                            firstPlayerName.setString(names[indexCharacter]);
                        }
                    }
                    else {
                        textFirstPlayerPrevious.setFillColor(sf::Color::Green);
                    }
                }
                else {
                    textFirstPlayerPrevious.setFillColor(TextInitializer::BetterWhite);
                }

                // Next character
                if(buttonFirstPlayerNext.getGlobalBounds().contains(mousePosition)) {
                    if(event.type == sf::Event::MouseButtonPressed) {
                        if(indexCharacter < (int)(characters.size() - 4)) {
                            indexCharacter++;
                            textureCharacter1.loadFromFile(characters[indexCharacter]);
                            spriteCharacter1.setTexture(textureCharacter1, true);
                            firstPlayerName.setString(names[indexCharacter]);
                        }
                    }
                    else {
                        textFirstPlayerNext.setFillColor(sf::Color::Green);
                    }
                }
                else {
                    textFirstPlayerNext.setFillColor(TextInitializer::BetterWhite);
                }
            }

            if(firstPlayerOk && !secondPlayerOk) {
                // Previous character
                if(buttonSecondPlayerPrevious.getGlobalBounds().contains(mousePosition)) {
                    if(event.type == sf::Event::MouseButtonPressed) {
                        if(indexCharacter + 3 > 3) {
                            indexCharacter--;
                            textureCharacter2.loadFromFile(characters[indexCharacter + 3]);
                            spriteCharacter2.setTexture(textureCharacter2, true);
                            secondPlayerName.setString(names[indexCharacter + 3]);
                        }
                    }
                    else {
                        textSecondPlayerPrevious.setFillColor(sf::Color::Green);
                    }
                }
                else {
                    textSecondPlayerPrevious.setFillColor(TextInitializer::BetterWhite);
                }

                // Next character
                if(buttonSecondPlayerNext.getGlobalBounds().contains(mousePosition)) {
                    if(event.type == sf::Event::MouseButtonPressed) {
                        if(indexCharacter + 3 < (int)(characters.size() - 1)) {
                            indexCharacter++;
                            textureCharacter2.loadFromFile(characters[indexCharacter + 3]);
                            spriteCharacter2.setTexture(textureCharacter2, true);
                            secondPlayerName.setString(names[indexCharacter + 3]);
                        }
                    }
                    else {
                        textSecondPlayerNext.setFillColor(sf::Color::Green);
                    }
                }
                else {
                    textSecondPlayerNext.setFillColor(TextInitializer::BetterWhite);
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
            if(event.type == sf::Event::MouseButtonPressed) return 0;
            else {
                textBack.setFillColor(TextInitializer::DarkerBetterRed);
            }
        }
        else {
            textBack.setFillColor(TextInitializer::BetterRed);
        }

        /// First player
        if(!firstPlayerOk) {
            if(buttonValidateFirstPlayer.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    firstPlayerOk = true;
                    textValidateFirstPlayer.setString("Validated");
                    textValidateFirstPlayer.setPosition(textValidateFirstPlayer.getPosition().x - 10, textValidateFirstPlayer.getPosition().y);
                    strFirstPlayerName = firstPlayerName.getString().toAnsiString();
                    pathSpriteFirstPlayer = spriteSheets[indexCharacter];

                    // Preparing for second player
                    textValidateSecondPlayer.setFillColor(TextInitializer::BetterWhite);
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
                    pathSpriteSecondPlayer = spriteSheets[indexCharacter + 3];
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

        app.draw(spriteCharacter1);

        app.draw(buttonFirstPlayerPrevious);
        app.draw(textFirstPlayerPrevious);

        app.draw(buttonFirstPlayerNext);
        app.draw(textFirstPlayerNext);

        app.draw(buttonValidateFirstPlayer);
        app.draw(textValidateFirstPlayer);

        // Second player elements
        app.draw(secondPlayerName);

        app.draw(spriteCharacter2);

        app.draw(buttonSecondPlayerPrevious);
        app.draw(textSecondPlayerPrevious);

        app.draw(buttonSecondPlayerNext);
        app.draw(textSecondPlayerNext);

        app.draw(buttonValidateSecondPlayer);
        app.draw(textValidateSecondPlayer);

        app.display();
    }

    return -1;
}

void PrematchScreen::initVectors() {
    maps.push_back("resources/images/previews/maps/map1_preview.png");
    maps.push_back("resources/images/previews/maps/map2_preview.png");

    names.push_back("Dark Golem");
    names.push_back("Dark Groot");
    names.push_back("Dark Minotaur");
    names.push_back("Light Golem");
    names.push_back("Light Groot");
    names.push_back("Light Minotaur");

    characters.push_back("resources/images/previews/characters/golem_dark.png");
    characters.push_back("resources/images/previews/characters/groot_dark.png");
    characters.push_back("resources/images/previews/characters/minotaur_dark.png");
    characters.push_back("resources/images/previews/characters/golem_light.png");
    characters.push_back("resources/images/previews/characters/groot_light.png");
    characters.push_back("resources/images/previews/characters/minotaur_light.png");

    spriteSheets.push_back("resources/images/characters/golem_dark.png");
    spriteSheets.push_back("resources/images/characters/groot_dark.png");
    spriteSheets.push_back("resources/images/characters/minotaur_dark.png");
    spriteSheets.push_back("resources/images/characters/golem_light.png");
    spriteSheets.push_back("resources/images/characters/groot_light.png");
    spriteSheets.push_back("resources/images/characters/minotaur_light.png");
}

void PrematchScreen::initBackground() {
    backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/background_other.jpg", position, &textureBackground);
}

void PrematchScreen::initPositions() {
    positionPlayerElements = {350, 200};
    positionButtonsMap = {860, 700};
    positionTextMap = {positionButtonsMap.getX() - 75, positionButtonsMap.getY() - 13};
}
