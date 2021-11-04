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
    music.setVolume(10.f);
    music.play();

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    float deltaTime;
    sf::Clock clock;

    // Initialize the player's position
    Position position(middleScreenX, middleScreenY);

    // Load sprite of player
    sf::Texture texturePlayerP1;
    sf::Texture texturePlayerP2;
    PlayerView playerViewP1 = createPlayer(4.0f, 4.0f, "resources/images/character/walk/mario_1_1.png", position, &texturePlayerP1,
                                         sf::Keyboard::Up,
                                         sf::Keyboard::Left,
                                         sf::Keyboard::Right,
                                         sf::Keyboard::Down);
    PlayerView playerViewP2 = createPlayer(4.0f, 4.0f, "resources/images/character/walk/mario_1_1.png", position, &texturePlayerP2,
                                         sf::Keyboard::Z,
                                         sf::Keyboard::Q,
                                         sf::Keyboard::D,
                                         sf::Keyboard::S);

    // Load background sprite
    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    //load texture for platforms
    sf::Texture textureBrick;

    //loading the first map
    MapView map1(2, &textureBrick,"resources/images/platform/platform_default.png" );

    //get all the platforms from the map
    vector<PlatformView> platforms = map1.getAllCollisions();

    // Create HealthBar
    Position posHealthBarP1(50.f, 50.f);
    Position posHealthBarP2(1550.f, 50.f);

    HealthBarView healthBarViewP1 = createHealthBar(playerViewP1.getPlayer(), posHealthBarP1);
    HealthBarView healthBarViewP2 = createHealthBar(playerViewP2.getPlayer(), posHealthBarP2);

    sf::Text namePlayerP1 = healthBarViewP1.createNamePlayer(playerViewP1.getPlayer(), posHealthBarP1);
    sf::Text namePlayerP2 = healthBarViewP2.createNamePlayer(playerViewP2.getPlayer(), posHealthBarP2);

    sf::Font font;
    font.loadFromFile("resources/fonts/arial.ttf");
    namePlayerP1.setFont(font);
    namePlayerP2.setFont(font);

    bool looksRightP1 = true;
    bool looksRightP2 = true;
	// Start the game loop
    while (app.isOpen()) {
        deltaTime = clock.restart().asMilliseconds();
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) app.close();
        }

        looksRightP1 = playerViewP1.movePlayer(
                                    playerViewP1.inputPlayer(deltaTime,playerViewP2),
                                    looksRightP1,
                                    directionCollisions(playerViewP1,platforms)
                                );
        looksRightP2 = playerViewP2.movePlayer(
                                    playerViewP2.inputPlayer(deltaTime,playerViewP1),
                                    looksRightP2,
                                    directionCollisions(playerViewP2,platforms)
                                );

        healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
        healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(backgroundSprite);
        app.draw(playerViewP1.getSprite());
        app.draw(playerViewP2.getSprite());

        for(auto i : map1.getPlatforms()){
            app.draw(i.getSprite());
        }

        app.draw(healthBarViewP1.getHealthBarIn());
        app.draw(healthBarViewP1.getHealthBarOut());

        app.draw(healthBarViewP2.getHealthBarIn());
        app.draw(healthBarViewP2.getHealthBarOut());

        app.draw(namePlayerP1);
        app.draw(namePlayerP2);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
