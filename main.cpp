#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "CoupleVectorTransformer.h"
#include "PlayerView.h"
#include "PlatformView.h"
#include "Collision.h"
#include "ObjectInitializer.h"
#include "MapView.h"
#include "HealthBar.h"
#include "HealthBarView.h"

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
    PlayerView playerView = createPlayer(.5f, .5f, "resources/images/character/mario.png", position, &texturePlayer,
                                         sf::Keyboard::Up,
                                         sf::Keyboard::Left,
                                         sf::Keyboard::Right);

    // Load background sprite
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    //load texture for platforms
    sf::Texture textureBrick;

    //loading the first map
    MapView map1(1,&textureBrick);

    //get all the platforms from the map
    vector<PlatformView> platforms = map1.getAllCollisions();

    // Create HealthBar
    sf::RectangleShape healthBarIn;
    sf::RectangleShape healthBarOut;

    HealthBar healthBar(70.f, 100.f, 100.f);
    HealthBarView healthBarView(&healthBar, healthBarIn, healthBarOut);

    healthBarView.setPositionHealthBarIn(50.f,50.f);
    healthBarView.setPositionHealthBarOut(50.f,50.f);

    healthBarView.addColorToHealthBarIn();
    healthBarView.addColorToHealthBarOut();

    healthBarView.addSizeToHealthBarIn();
    healthBarView.addSizeToHealthBarOut();

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

        looksRight = playerView.movePlayer(playerView.inputPlayer(deltaTime), looksRight, directionCollisions(playerView,platforms));

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerView.getSprite());
        for(auto i : map1.getPlatforms()){
            app.draw(i.getSprite());
        }

        app.draw(healthBarView.getHealthBarIn());
        app.draw(healthBarView.getHealthBarOut());

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
