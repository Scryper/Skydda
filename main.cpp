#include <SFML/Graphics.hpp>

#include <iostream>

#include "TextureLoader.h"
#include "CoupleVectorTransformer.h"
#include "Player.h"
#include "PlayerView.h"
#include "Platform.h"
#include "PlatformView.h"
#include "Collision.h"

using namespace std;

sf::Sprite initSprite(float sizeX, float sizeY, string pathToSprite, Position position, sf::Texture *texture) {
    CoupleFloat couple(sizeX, sizeY);
    Size sizeOfSprite(couple);
    sf::Sprite sprite = loadTexture(pathToSprite, sizeOfSprite, position, *texture);
    return sprite;
}

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
    // Initialize speed, velocity and movement
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.5f, .5f);
    CoupleFloat maxSpeed(10.f, 10.f);

    Movement movement(velocity, acceleration, maxSpeed);
    // Load sprite of player
    sf::Texture texturePlayer;
    sf::Sprite playerSprite = initSprite(.5f, .5f, "resources/images/character/mario.png", position, &texturePlayer);
    // create player and his view
    Player player("Scryper", 100, true, 100, position, movement);
    PlayerView playerView(playerSprite, player);

    // Load background sprite
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);


    CoupleFloat coupleBrickSprite(.3f, .3f);
    Size sizeBrickSprite(coupleBrickSprite);

    position.setY(position.getY() + 350);
    sf::Texture textureBrick;
    sf::Sprite brickSprite = initSprite(.3f, .3f, "resources/images/platform/platform_default.png", position, &textureBrick);

    Position posBrick(position.getY(), position.getY()+350);
    Platform platformBrick(posBrick, sizeBrickSprite);
    PlatformView platformViewBrick(brickSprite, platformBrick);

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

        cout << "directionCollision : " << directionCollision(playerView,platformViewBrick) << endl;

        switch(directionCollision(playerView,platformViewBrick)) {
            case 1:
                vector2f.y += 50.f;
                looksRight = playerView.movePlayer(vector2f, looksRight);
                break;
            case 2:
                vector2f.y -= 50.f;
                looksRight = playerView.movePlayer(vector2f, looksRight);
                break;
            case 3:
                vector2f.x += 50.f;
                looksRight = playerView.movePlayer(vector2f, looksRight);
                break;
            case 4:
                vector2f.x -= 50.f;
                looksRight = playerView.movePlayer(vector2f, looksRight);
                break;
            case -1:
                looksRight = playerView.movePlayer(vector2f, looksRight);
            default:
                break;
        }

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
