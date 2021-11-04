#include <SFML/Audio.hpp>
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

    sf::Music music;
    if(!music.openFromFile("resources/audio/fight_theme.ogg")) {
        cout << "Music was not found" << endl;
    }
    music.play();

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    float deltaTime;
    sf::Clock clock;

    // Initialize the player's position
    Position position(middleScreenX, middleScreenY);

    // Load sprite of player
    sf::Texture texturePlayer;
    sf::Texture texturePlayer2;
    PlayerView playerView = createPlayer(.5f, .5f, "resources/images/character/mario.png", position, &texturePlayer,
                                         sf::Keyboard::Up,
                                         sf::Keyboard::Left,
                                         sf::Keyboard::Right);
    PlayerView playerView2 = createPlayer(.5f, .5f, "resources/images/character/mario.png", position, &texturePlayer2,
                                         sf::Keyboard::Z,
                                         sf::Keyboard::Q,
                                         sf::Keyboard::D);

    // Load background sprite
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    //load texture for platforms
    sf::Texture textureBrick;

    //loading the first map
    MapView map1(2, &textureBrick);

    //get all the platforms from the map
    vector<PlatformView> platforms = map1.getAllCollisions();

    // Create HealthBar
    Position posHealthBar(50.f, 50.f);
    HealthBarView healthBarView = createHealthBar(playerView.getPlayer(), posHealthBar);

    sf::Text namePlayer = healthBarView.createNamePlayer(playerView.getPlayer(), posHealthBar);
    sf::Font font;
    font.loadFromFile("resources/fonts/arial.ttf");
    namePlayer.setFont(font);

    bool looksRight = true;
    bool looksRight2 = true;
	// Start the game loop
    while (app.isOpen()) {
        deltaTime = clock.restart().asMilliseconds();
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) app.close();
        }

        looksRight = playerView.movePlayer(
                                    playerView.inputPlayer(deltaTime),
                                    looksRight,
                                    directionCollisions(playerView,platforms)
                                );
        looksRight2 = playerView2.movePlayer(
                                    playerView2.inputPlayer(deltaTime),
                                    looksRight2,
                                    directionCollisions(playerView2,platforms)
                                );

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerView.getSprite());
        app.draw(playerView2.getSprite());

        for(auto i : map1.getPlatforms()){
            app.draw(i.getSprite());
        }

        app.draw(healthBarView.getHealthBarIn());
        app.draw(healthBarView.getHealthBarOut());

        app.draw(namePlayer);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
