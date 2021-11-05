#include "OptionScreen.h"

int OptionScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    sf::Event event;

    sf::Vector2f mousePosition;

    Position position = getScreenCenter(&app);
    Position positionText(position.getX() - 75, position.getY() - 12);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    /// Load Button
    sf::Texture textureButton;
    sf::Sprite buttonBack = initSprite(.5f, 1.f, "resources/images/button/button.png", position, &textureButton);
    // Text of buttonQuit
    positionText.setX(positionText.getX() + 35);
    sf::Text textBack = TextInitializer::createText("Back", positionText);
    textBack.setFillColor(TextInitializer::BetterRed);

    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");

    std::vector<sf::Text*> texts;
    texts.push_back(&textBack);

    TextInitializer::initFont(texts, &font);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;
        }

        // Get the mouse position to verify if the user is over a sprite and/or click a sprite
        mousePosition = getMousePosition(&app);

        /// Button quit
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

        // Draw elements
        app.draw(backgroundSprite);

        app.draw(buttonBack);
        app.draw(textBack);

        app.display();
    }

    return -1;
}
