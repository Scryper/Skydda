#include <SFML/Graphics.hpp>

#include <iostream>

#include "TextureLoader.h"
#include "CoupleVectorTransformer.h"
#include "Player.h"
#include "PlayerView.h"

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
    float deltaTime;
    sf::Clock clock;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    // Initialise the player's position
    Position position(middleScreenX, middleScreenY);
    // Initialize speed, velocity and movement
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(2.f, 2.f);
    CoupleFloat maxSpeed(10.0f, 10.0f);

    Movement movement(velocity, acceleration, maxSpeed);
    // Load sprite of player
    CoupleFloat couplePlayerSprite(0.5f, 0.5f);
    Size sizePlayerSprite(couplePlayerSprite);
    sf::Texture texturePlayer;
    sf::Sprite playerSprite = loadTexture("resources/images/character/mario.png", sizePlayerSprite, position, texturePlayer);
    // create player and his view
    Player player("Scryper", 100, true, 100, position, movement);
    PlayerView playerView(playerSprite, player);

    CoupleFloat coupleBackgroundSprite(1.f, 1.f);
    Size sizeBackgroundSprite(coupleBackgroundSprite);
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = loadTexture("resources/images/background/mario_fond.png", sizeBackgroundSprite, position, textureBackground);

    CoupleFloat coupleBrickSprite(0.2f, 0.2f);
    Size sizeBrickSprite(coupleBrickSprite);
    position.setX(position.getX() + 150);
    sf::Texture textureBrick;
    sf::Sprite brickSprite = loadTexture("resources/images/platform/brick.png", sizeBrickSprite, position, textureBrick);

//    std::cout << player.getPosition().getX() << ":" << player.getPosition().getY() << std::endl;
//    Position ptest(middleScreenX + 120, middleScreenY + 120);
//    player.setPosition(ptest);
//    playerSprite.setPosition(middleScreenX + 120, middleScreenY + 120);
//    std::cout << player.getPosition().getX() << ":" << player.getPosition().getY() << std::endl;

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
        looksRight = playerView.movePlayer(vector2f, looksRight);
        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerView.getSprite());
        app.draw(brickSprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
