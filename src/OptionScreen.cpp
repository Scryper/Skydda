#include "OptionScreen.h"

int OptionScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    position = getScreenCenter(&app);

    /// Load background
    initBackground();

    /// Load music infos
    position.setX(position.getX() - 225);
    position.setY(position.getY() - 300);
    // value
    textValueOfVolume = TextInitializer::createText(TEXT_VOLUME + std::to_string((int) GlobalVariables::VOLUME_MUSIC), position);
    textValueOfVolume.setCharacterSize(60);

    // Buttons
    position.setX(1220);
    position.setY(242);
    buttonPlus = initSprite(1.5f, 1.5f, PATH_ARROW, position, &textureButtonPlusMinus);

    position.setX(1220);
    position.setY(312);
    buttonMinus = initSprite(1.5f, -1.5f, position, &textureButtonPlusMinus);

    /// Load Button
    position.setX(100);
    position.setY(1020);
    buttonBack = initSprite(.5f, 1.f, PATH_BUTTON, position, &textureButton);
    // Text of buttonQuit
    position.setX(60);
    position.setY(1008);
    textBack = TextInitializer::createText(TEXT_BACK, position);
    textBack.setFillColor(TextInitializer::BetterRed);

    // ControlsP1
    position.setX(600);
    position.setY(700);
    spriteControlsP1 = initSprite(0.25f, 0.25f, PATH_CONTROLS_P1, position, &textureControlsP1);

    // ControlsP2
    position.setX(1400);
    position.setY(700);
    spriteControlsP2 = initSprite(0.25f, 0.25f, PATH_CONTROLS_P2, position, &textureControlsP2);

    initFonts();

    sf::Event event;
    while(app.isOpen()) {
        // Get the mouse position to verify if the user is over a sprite and/or click a sprite
        mousePosition = getMousePosition(&app);

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;

            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
                buttonPlus.setColor(sf::Color::Green);
                changeVolume(1.f);
            } else {
                buttonPlus.setColor(TextInitializer::BetterWhite);
            }

            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
                buttonMinus.setColor(sf::Color::Green);
                changeVolume(-1.f);
            } else {
                buttonMinus.setColor(TextInitializer::BetterWhite);
            }

            /// Button plus
            if(buttonPlus.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    changeVolume(1.f); // volume up
                }
                else {
                    buttonPlus.setColor(sf::Color::Green);
                }
            }
            else {
                if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    buttonPlus.setColor(TextInitializer::BetterWhite);
                }
            }

            /// Button minus
            if(buttonMinus.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    changeVolume(-1.f); // volume down
                }
                else {
                    buttonMinus.setColor(sf::Color::Green);
                }
            }
            else {
                if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    buttonMinus.setColor(TextInitializer::BetterWhite);
                }
            }
        }

        /// Button quit
        if(buttonBack.getGlobalBounds().contains(mousePosition)) {
            if(event.type == sf::Event::MouseButtonPressed) return 0;
            else {
                textBack.setFillColor(TextInitializer::DarkerBetterRed);
            }
        }
        else {
            textBack.setFillColor(TextInitializer::BetterRed);
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);

        app.draw(textValueOfVolume);

        app.draw(buttonPlus);
        app.draw(buttonMinus);

        app.draw(buttonBack);
        app.draw(textBack);

        app.draw(spriteControlsP1);
        app.draw(spriteControlsP2);

        app.display();
    }
    return -1;
}

void OptionScreen::initBackground() {
    backgroundSprite = initSprite(1.f, 1.f, PATH_BACKGROUND_OTHER, position, &textureBackground);
}

void OptionScreen::initFonts() {
    font.loadFromFile(PATH_FONT);

    texts.push_back(&textBack);
    texts.push_back(&textValueOfVolume);

    TextInitializer::initFont(texts, &font);
}

void OptionScreen::changeVolume(float value) {
    if(GlobalVariables::VOLUME_MUSIC + value >= 0 && GlobalVariables::VOLUME_MUSIC + value <= 100) {
        GlobalVariables::VOLUME_MUSIC += value;
        textValueOfVolume.setString(TEXT_VOLUME + std::to_string((int) GlobalVariables::VOLUME_MUSIC));
        musicManager->changeVolume(GlobalVariables::VOLUME_MUSIC);
    }
}
