#include "GameScreen.h"
#include "Match.h"

int GameScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    float deltaTime;
    sf::Clock clock;

    Position position = getScreenCenter(&app);
    Position positionP1(position.getX() - 500, position.getY());
    Position positionP2(position.getX() + 500, position.getY());

    CoupleFloat scaleP1(4.f, 4.f);
    CoupleFloat scaleP2(4.f, 4.f);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/mario_fond.png", position, &textureBackground);

    // Load sprite of player
    sf::Texture texturePlayerP1;
    PlayerView playerViewP1 = createPlayer(scaleP1.getX(), scaleP1.getY(), "resources/images/character/walk/mario_1_1.png", positionP1, &texturePlayerP1,
                                          sf::Keyboard::Z,
                                          sf::Keyboard::Q,
                                          sf::Keyboard::D,
                                          sf::Keyboard::S,
                                          sf::Keyboard::LShift,
                                          true,
                                          "Scryper");

    sf::Texture texturePlayerP2;
    PlayerView playerViewP2 = createPlayer(scaleP2.getX(), scaleP2.getY(), "resources/images/character/walk/mario_1_1.png", positionP2, &texturePlayerP2,
                                         sf::Keyboard::Up,
                                         sf::Keyboard::Left,
                                         sf::Keyboard::Right,
                                         sf::Keyboard::Down,
                                         sf::Keyboard::RShift,
                                         false,
                                         "Damien");
    playerViewP2.flipSprite();

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

    // Create posNamePlayer
    Position posNamePlayerP1(50.f, 80.f);
    Position posNamePlayerP2(1550.f, 80.f);
    sf::Text namePlayerP1 = healthBarViewP1.createNamePlayer(playerViewP1.getPlayer(), posNamePlayerP1);
    sf::Text namePlayerP2 = healthBarViewP2.createNamePlayer(playerViewP2.getPlayer(), posNamePlayerP2);

    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    namePlayerP1.setFont(font);
    namePlayerP2.setFont(font);

    Match match(playerViewP1.getPlayer(), playerViewP2.getPlayer());

    while(app.isOpen()) {
        cout << "isAlive1 : " << playerViewP1.getPlayer().isAlive() << endl;
        cout << "isAlive2 : " << playerViewP2.getPlayer().isAlive() << endl;
        //playerViewP2.getPlayer().setAlive(false);
        //match.getPlayer1().setAlive(false);

        deltaTime = clock.restart().asMilliseconds();

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return -1;
            }
        }

        playerViewP1.movePlayer(
                                    playerViewP1.inputPlayer(deltaTime, playerViewP2),
                                    directionCollisions(playerViewP1, platforms)
                                );

        playerViewP2.movePlayer(
                                    playerViewP2.inputPlayer(deltaTime, playerViewP1),
                                    directionCollisions(playerViewP2, platforms)
                                );

        healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
        healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());

         if(match.getPlayerWin() == 0) {
            if(playerViewP1.getPlayer().getHealth() == 0) {
                match.incrementRoundWinP2();
                if(match.getPlayerWin() == 0)playerViewP1.setHealth(100.f);
            }
            if(playerViewP2.getPlayer().getHealth() == 0) {
                match.incrementRoundWinP1();
                if(match.getPlayerWin() == 0)playerViewP2.setHealth(100.f);
            }
        } else {
            match.win();
        }

        cout << "P1 victoire : " << match.getRoundWinP1() << endl;
        cout << "P2 victoire : " << match.getRoundWinP2() << endl;

        app.clear();

        // Draw elements
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
