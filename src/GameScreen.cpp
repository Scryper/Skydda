#include "GameScreen.h"

GameScreen::GameScreen() { }

GameScreen::~GameScreen() { }

int GameScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    int middleScreenX = app.getSize().x / 2.;
    int middleScreenY = app.getSize().y / 2.;

    float deltaTime;
    sf::Clock clock;

    Position position(middleScreenX, middleScreenY);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    // Load sprite of player
    sf::Texture texturePlayerP1;
    sf::Texture texturePlayerP2;
    PlayerView playerViewP1 = createPlayer(4.f, 4.f, "resources/images/character/walk/mario_1_1.png", position, &texturePlayerP1,
                                         sf::Keyboard::Up,
                                         sf::Keyboard::Left,
                                         sf::Keyboard::Right,
                                         sf::Keyboard::Down);
    PlayerView playerViewP2 = createPlayer(3.f, 4.f, "resources/images/character/walk/mario_1_1.png", position, &texturePlayerP2,
                                         sf::Keyboard::Z,
                                         sf::Keyboard::Q,
                                         sf::Keyboard::D,
                                         sf::Keyboard::S);

    //load texture for platforms
    sf::Texture textureBrick;

    //loading the first map
    MapView map1(2, &textureBrick, "resources/images/platform/platform_default.png");

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

    while(app.isOpen()) {
        deltaTime = clock.restart().asMilliseconds();

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        looksRightP1 = playerViewP1.movePlayer(
                                    playerViewP1.inputPlayer(deltaTime, playerViewP2),
                                    looksRightP1,
                                    directionCollisions(playerViewP1, platforms)
                                );

        looksRightP2 = playerViewP2.movePlayer(
                                    playerViewP2.inputPlayer(deltaTime, playerViewP1),
                                    looksRightP2,
                                    directionCollisions(playerViewP2, platforms)
                                );

        healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
        healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());

        app.clear();

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

        app.display();
    }

    return -1;
}
