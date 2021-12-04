#include "OptionScreen.h"

int OptionScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    position = getScreenCenter(&app);

    /// Load background
    initBackground();

    Position positionText(position.getX() - 75, position.getY() - 12);

    /// Load music infos
    positionText.setX(positionText.getX() - 150);
    // value
    textValueOfVolume = TextInitializer::createText("Volume   " + std::to_string((int) GlobalVariables::VOLUME_MUSIC), positionText);
    textValueOfVolume.setCharacterSize(35);

    // Buttons
    position.setX(position.getX() + 100);
    position.setY(position.getY() - 10);
    buttonPlus = initSprite(1.f, 1.f, "resources/images/arrows/arrow.png", position, &textureButtonPlusMinus);

    position.setY(position.getY() + 50);
    buttonMinus = initSprite(1.f, 1.f, position, &textureButtonPlusMinus);
    buttonMinus.setScale(1.f, -1.f);

    /// Load Button
    positionText.setX(positionText.getX() + 150);
    position.setY(position.getY() + 260);
    position.setX(position.getX() - 100);
    buttonBack = initSprite(.5f, 1.f, "resources/images/buttons/button.png", position, &textureButton);
    // Text of buttonQuit
    positionText.setX(positionText.getX() + 35);
    positionText.setY(positionText.getY() + 300);
    textBack = TextInitializer::createText("Back", positionText);
    textBack.setFillColor(TextInitializer::BetterRed);

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
                    changeVolume(1.f);
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
                    changeVolume(-1.f);
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

        app.display();
    }
    return -1;
}

void OptionScreen::initBackground() {
    backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/background_other.jpg", position, &textureBackground);
}

void OptionScreen::initFonts() {
    font.loadFromFile("resources/fonts/glitch.otf");

    texts.push_back(&textBack);
    texts.push_back(&textValueOfVolume);

    TextInitializer::initFont(texts, &font);
}

void OptionScreen::changeVolume(float value) {
    if(GlobalVariables::VOLUME_MUSIC + value >= 0 && GlobalVariables::VOLUME_MUSIC + value <= 100) {
        GlobalVariables::VOLUME_MUSIC += value;
        textValueOfVolume.setString("Volume   " + std::to_string((int) GlobalVariables::VOLUME_MUSIC));
        musicManager->changeVolume(GlobalVariables::VOLUME_MUSIC);
    }
}
