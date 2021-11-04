#include "MenuScreen.h"

MenuScreen::MenuScreen() { }

MenuScreen::~MenuScreen() { }

int MenuScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    Position position(middleScreenX, middleScreenY);

    sf::Texture textureBackground;
    sf::Sprite background = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    sf::Texture textureButton;
    sf::Sprite button = initSprite(.5f, .5f, "resources/images/platform/brick.png", position, &textureButton);

    while(app.isOpen()) {
        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(app);
        sf::Vector2f adaptedPosition = app.mapPixelToCoords(mousePosition);

        if(event.type == sf::Event::MouseButtonPressed
           && button.getGlobalBounds().contains(adaptedPosition)) {
            return 1;
        }

        app.clear();

        app.draw(background);
        app.draw(button);

        app.display();
    }

    return -1;
}
