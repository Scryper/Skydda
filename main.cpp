#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "CoupleVectorTransformer.h"
#include "PlayerView.h"
#include "PlatformView.h"
#include "Collision.h"
#include "ObjectInitializer.h"

using namespace std;

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
    app.setFramerateLimit(60);

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    float deltaTime;
    sf::Clock clock;

    // Initialize the player's position
    Position position(middleScreenX, middleScreenY);

    // Load sprite of player
    sf::Texture texturePlayer;
    PlayerView playerView = createPlayer(.5f, .5f, "resources/images/character/mario.png", position, &texturePlayer);

    // Load background sprite
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    position.setY(position.getY() + 350);
    position.setX(position.getX() + 300);
    sf::Texture textureBrick;
    sf::Sprite brickSprite = initSprite(.3f, .3f, "resources/images/platform/platform_default.png", position, &textureBrick);

    PlatformView platformViewBrick = createPlatform(1.f, .3f, "resources/images/platform/platform_default.png", position, &textureBrick);

    Position bottomPlatformPosition(position.getX() - 900, position.getY() -200);
    PlatformView bottomPlatform = createPlatform(1.f, .3f, "resources/images/platform/platform_default.png", bottomPlatformPosition, &textureBrick);


    vector<PlatformView> platforms;
    platforms.push_back(platformViewBrick);
    platforms.push_back(bottomPlatform);


    bool looksRight = true;
	// Start the game loop
    while (app.isOpen()) {
        deltaTime = clock.restart().asMilliseconds();
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) app.close();
        }

        // Movement
        sf::Vector2f vector2f(0.f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            vector2f.y += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            vector2f.y += deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            vector2f.x += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            vector2f.x += deltaTime;
        }

        looksRight = playerView.movePlayer(vector2f, looksRight, directionCollisions(playerView,platforms));

        float SIZEDEMIPLAYER = playerView.getSprite().getGlobalBounds().width/2;

        if(playerView.getPlayer().getPosition().getX() + SIZEDEMIPLAYER < 0.f) {
            playerView.stopX();
        }

        if(playerView.getPlayer().getPosition().getX() + SIZEDEMIPLAYER > 1920.f ) {
            playerView.stopX();
        }

        if(playerView.getPlayer().getPosition().getY() > 1080.f) {
            playerView.stopY();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerView.getSprite());
        app.draw(platformViewBrick.getSprite());
        app.draw(bottomPlatform.getSprite());

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
