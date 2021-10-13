#include <SFML/Graphics.hpp>

#include "TextureLoader.h"

int main() {
    // Create the main window
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow app(
        sf::VideoMode(
            desktopMode.width,
            desktopMode.height,
            desktopMode.bitsPerPixel),
        "Skydda",
        sf::Style::Fullscreen
    );

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    CoupleFloat couplePlayerSprite(0.5f, 0.5f);
    Size sizePlayerSprite(couplePlayerSprite);
    Position position(middleScreenX, middleScreenY);
    sf::Texture texturePlayer;
    sf::Sprite playerSprite = loadTexture("resources/images/character/mario.png", sizePlayerSprite, position, texturePlayer);

    CoupleFloat coupleBackgroundSprite(1.f, 1.f);
    Size sizeBackgroundSprite(coupleBackgroundSprite);
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = loadTexture("resources/images/background/mario_fond.png", sizeBackgroundSprite, position, textureBackground);

    CoupleFloat coupleBrickSprite(0.2f, 0.2f);
    Size sizeBrickSprite(coupleBrickSprite);
    position.setX(position.getX() + 150);
    sf::Texture textureBrick;
    sf::Sprite brickSprite = loadTexture("resources/images/platform/brick.png", sizeBrickSprite, position, textureBrick);

	// Start the game loop
    while (app.isOpen()) {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerSprite);
        app.draw(brickSprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
