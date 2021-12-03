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
    spriteCharacter1 = initSprite(1.f, 1.f, characters[indexCharacter1], positionPlayerElements, &textureCharacter1);

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

    /// Second player elements
    //Reset
    positionPlayerElements.setX(position.getX() * 2 - 500);
    positionPlayerElements.setY(positionPlayerElements.getY() - 490);

    // Name
    positionPlayerElements.setX(positionPlayerElements.getX() + 50);
    secondPlayerName = TextInitializer::createText("Light Golem", positionPlayerElements);

    // Show selected character
    positionPlayerElements.setX(positionPlayerElements.getX() + 100);
    positionPlayerElements.setY(positionPlayerElements.getY() + 300);
    spriteCharacter2 = initSprite(1.f, 1.f, characters[indexCharacter2], positionPlayerElements, &textureCharacter2);

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

    /// Mode choosing elements
    Position positionModeChoosing(position.getX() - 150, 200);
    textMode = TextInitializer::createText("Choose game mode", positionModeChoosing);

    positionModeChoosing.setY(positionModeChoosing.getY() + 80);
    positionModeChoosing.setX(positionModeChoosing.getX() + 50);
    buttonModeRounds = initSprite(.7f, 1.f, positionModeChoosing, &textureButton);
    positionModeChoosing.setY(positionModeChoosing.getY() - 12);
    positionModeChoosing.setX(positionModeChoosing.getX() - 65);
    textModeRounds = TextInitializer::createText("Rounds", positionModeChoosing);

    positionModeChoosing.setX(positionModeChoosing.getX() + 265);
    positionModeChoosing.setY(positionModeChoosing.getY() + 12);
    buttonModeTime = initSprite(.7f, 1.f, positionModeChoosing, &textureButton);
    positionModeChoosing.setY(positionModeChoosing.getY() - 12);
    positionModeChoosing.setX(positionModeChoosing.getX() - 35);
    textModeTime = TextInitializer::createText("Time", positionModeChoosing);

    Position positionGameMode(position.getX(), 350);

    spriteMode = initSprite(.5f, .5f, gameModes[gameMode - 2], positionGameMode, &textureGameMode);

    /// Map elements
    Position positionMap(position.getX() - 125, 400);

    textMap = TextInitializer::createText("Choose the map", positionMap);

    positionMap.setY(positionMap.getY() + 150);
    positionMap.setX(positionMap.getX() + 125);
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
    initFonts();

    TextInitializer::initFont(texts, &font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }

            /// Next map
            if(buttonNextMap.getGlobalBounds().contains(mousePosition)) {
                textNextMap.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexMap < (int)(maps.size() - 1)) {
                        indexMap++;
                        textureMap.loadFromFile(maps[indexMap]);
                        spriteMap.setTexture(textureMap, true);
                    }
                }
            }
            else {
                textNextMap.setFillColor(TextInitializer::BetterWhite);
            }

            /// Previous map
            if(buttonPreviousMap.getGlobalBounds().contains(mousePosition)) {
                textPreviousMap.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexMap > 0) {
                        indexMap--;
                        textureMap.loadFromFile(maps[indexMap]);
                        spriteMap.setTexture(textureMap, true);
                    }
                }
            }
            else {
                textPreviousMap.setFillColor(TextInitializer::BetterWhite);
            }

            // Previous character
            if(buttonFirstPlayerPrevious.getGlobalBounds().contains(mousePosition)) {
                textFirstPlayerPrevious.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexCharacter1 > 0) {
                        indexCharacter1--;
                        textureCharacter1.loadFromFile(characters[indexCharacter1]);
                        spriteCharacter1.setTexture(textureCharacter1, true);
                        firstPlayerName.setString(names[indexCharacter1]);
                    }
                }
            }
            else {
                textFirstPlayerPrevious.setFillColor(TextInitializer::BetterWhite);
            }

            // Next character
            if(buttonFirstPlayerNext.getGlobalBounds().contains(mousePosition)) {
                textFirstPlayerNext.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexCharacter1 < (int)(characters.size() - 4)) {
                        indexCharacter1++;
                        textureCharacter1.loadFromFile(characters[indexCharacter1]);
                        spriteCharacter1.setTexture(textureCharacter1, true);
                        firstPlayerName.setString(names[indexCharacter1]);
                    }
                }
            }
            else {
                textFirstPlayerNext.setFillColor(TextInitializer::BetterWhite);
            }

            // Previous character
            if(buttonSecondPlayerPrevious.getGlobalBounds().contains(mousePosition)) {
                textSecondPlayerPrevious.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexCharacter2 > 3) {
                        indexCharacter2--;
                        textureCharacter2.loadFromFile(characters[indexCharacter2]);
                        spriteCharacter2.setTexture(textureCharacter2, true);
                        secondPlayerName.setString(names[indexCharacter2]);
                    }
                }
            }
            else {
                textSecondPlayerPrevious.setFillColor(TextInitializer::BetterWhite);
            }

            // Next character
            if(buttonSecondPlayerNext.getGlobalBounds().contains(mousePosition)) {
                textSecondPlayerNext.setFillColor(sf::Color::Green);
                if(event.type == sf::Event::MouseButtonPressed) {
                    if(indexCharacter2 < (int)(characters.size() - 1)) {
                        indexCharacter2++;
                        textureCharacter2.loadFromFile(characters[indexCharacter2]);
                        spriteCharacter2.setTexture(textureCharacter2, true);
                        secondPlayerName.setString(names[indexCharacter2]);
                    }
                }
            }
            else {
                textSecondPlayerNext.setFillColor(TextInitializer::BetterWhite);
            }
        }

        mousePosition = getMousePosition(&app);

        /// Button rounds mode
        if(buttonModeRounds.getGlobalBounds().contains(mousePosition)) {
            textModeRounds.setFillColor(sf::Color::Green);
            if(event.type == sf::Event::MouseButtonPressed) {
                gameMode = 2;
                textureGameMode.loadFromFile(gameModes[gameMode - 2]);
                spriteMode.setTexture(textureGameMode, true);
            }
        }
        else {
            textModeRounds.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button time mode
        if(buttonModeTime.getGlobalBounds().contains(mousePosition)) {
            textModeTime.setFillColor(sf::Color::Green);
            if(event.type == sf::Event::MouseButtonPressed) {
                gameMode = 3;
                textureGameMode.loadFromFile(gameModes[gameMode - 2]);
                spriteMode.setTexture(textureGameMode, true);
            }
        }
        else {
            textModeTime.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button play
        if(buttonPlay.getGlobalBounds().contains(mousePosition)) {
            textPlay.setFillColor(sf::Color::Green);
            if(event.type == sf::Event::MouseButtonPressed) {
                map_ = indexMap + 1;

                strFirstPlayerName = firstPlayerName.getString().toAnsiString();
                pathSpriteFirstPlayer = spriteSheets[indexCharacter1];

                strSecondPlayerName = secondPlayerName.getString().toAnsiString();
                pathSpriteSecondPlayer = spriteSheets[indexCharacter2];
                return gameMode;
            }
        }
        else {
            textPlay.setFillColor(TextInitializer::BetterWhite);
        }

        /// Button back
        if(buttonBack.getGlobalBounds().contains(mousePosition)) {
            textBack.setFillColor(TextInitializer::DarkerBetterRed);
            if(event.type == sf::Event::MouseButtonPressed) return 0;
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

        // Choose mode elements
        app.draw(textMode);

        app.draw(buttonModeRounds);
        app.draw(textModeRounds);

        app.draw(buttonModeTime);
        app.draw(textModeTime);

        app.draw(spriteMode);

        // Map element
        app.draw(textMap);

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

        // Second player elements
        app.draw(secondPlayerName);

        app.draw(spriteCharacter2);

        app.draw(buttonSecondPlayerPrevious);
        app.draw(textSecondPlayerPrevious);

        app.draw(buttonSecondPlayerNext);
        app.draw(textSecondPlayerNext);

        app.display();
    }

    return -1;
}

void PrematchScreen::initVectors() {
    maps.push_back("resources/images/previews/maps/map1_preview.png");
    maps.push_back("resources/images/previews/maps/map2_preview.png");
    maps.push_back("resources/images/previews/maps/map3_preview.png");

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

    gameModes.push_back("resources/images/gamemode/rounds.png");
    gameModes.push_back("resources/images/gamemode/timer.png");
}

void PrematchScreen::initBackground() {
    backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/background_other.jpg", position, &textureBackground);
}

void PrematchScreen::initPositions() {
    positionPlayerElements = {350, 200};
    positionButtonsMap = {860, 700};
    positionTextMap = {positionButtonsMap.getX() - 75, positionButtonsMap.getY() - 13};
}

void PrematchScreen::initFonts() {
    font.loadFromFile("resources/fonts/glitch.otf");

    texts.push_back(&textPlay);
    texts.push_back(&textBack);
    texts.push_back(&firstPlayerName);
    texts.push_back(&secondPlayerName);
    texts.push_back(&textMap);
    texts.push_back(&textNextMap);
    texts.push_back(&textPreviousMap);
    texts.push_back(&textFirstPlayerNext);
    texts.push_back(&textFirstPlayerPrevious);
    texts.push_back(&textSecondPlayerNext);
    texts.push_back(&textSecondPlayerPrevious);
    texts.push_back(&textMode);
    texts.push_back(&textModeRounds);
    texts.push_back(&textModeTime);
}
