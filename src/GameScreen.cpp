#include "GameScreen.h"
#include "Match.h"
#include "MatchView.h"

int GameScreen::run(sf::RenderWindow &app) {
    sf::Event event;

    float deltaTime;
    sf::Clock clock;

    Position position = getScreenCenter(&app);
    Position positionP1(position.getX() - 500, position.getY());
    Position positionP2(position.getX() + 500, position.getY());

    CoupleFloat scaleP1(2.f, 2.f);
    CoupleFloat scaleP2(2.f, 2.f);
    CoupleFloat textureLink(72.8f, 78.375f);

    sf::Texture textureBackground;
    sf::Sprite backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/background1.png", position, &textureBackground);

    // Load sprite of player
    sf::Texture texturePlayerP1;
    PlayerView playerViewP1 = createPlayer(scaleP1.getX(),
                                           scaleP1.getY(),
                                           textureLink.getX(),
                                           textureLink.getY(),
                                           "resources/images/character/link.png",
                                           positionP1,
                                           &texturePlayerP1,
                                           sf::Keyboard::Z,
                                           sf::Keyboard::Q,
                                           sf::Keyboard::D,
                                           sf::Keyboard::S,
                                           sf::Keyboard::LShift,
                                           true,
                                           "Scryper");

    sf::Texture texturePlayerP2;
    PlayerView playerViewP2 = createPlayer(scaleP2.getX(),
                                            scaleP2.getY(),
                                            textureLink.getX(),
                                            textureLink.getY(),
                                            "resources/images/character/link.png",
                                            positionP2,
                                            &texturePlayerP2,
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
    MapView map1(1, &textureBrick, "resources/images/platform/platform_default.png");

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

    MatchView matchView(match);

    Position posRoundCirclesP1(60.f,135.f);
    Position posRoundCirclesP2(1360.f,135.f);

    matchView.createRoundCircles(posRoundCirclesP1,posRoundCirclesP2);

    while(app.isOpen()) {

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

         if(matchView.getMatch().getPlayerWin() == 0) {
            if(playerViewP1.getPlayer().getHealth() == 0) {
                matchView.getMatch().incrementRoundWinP2();

//                cout << "pos : " << positionP1.getX() << ", " << positionP1.getY() << endl;
                matchView.getMatch().getPlayer1().setPosition(positionP1.getX(), positionP1.getY()-500);
                matchView.getMatch().getPlayer2().setPosition(positionP2.getX(), positionP2.getY()-500);

                if(matchView.getMatch().getPlayerWin() == 0) {
                        playerViewP1.setHealth(100.f);
                        playerViewP2.setHealth(100.f);
                }
            }
            if(playerViewP2.getPlayer().getHealth() == 0) {
                matchView.getMatch().incrementRoundWinP1();

//                cout << "pos : " << positionP1.getX() << ", " << positionP1.getY() << endl;
                matchView.getMatch().getPlayer1().setPosition(positionP1.getX(), positionP1.getY()-500);
                matchView.getMatch().getPlayer2().setPosition(positionP2.getX(), positionP2.getY()-500);

                if(matchView.getMatch().getPlayerWin() == 0){
                        playerViewP1.setHealth(100.f);
                        playerViewP2.setHealth(100.f);
                }
            }
        } else {
            matchView.getMatch().win();
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);
        app.draw(playerViewP1.getSprite());
        app.draw(playerViewP2.getSprite());

        for(auto i : map1.getPlatforms()){
            app.draw(i.getSprite());
        }



        for(auto i : matchView.getRoundCirclesP1()){
            app.draw(i);
        }

        for(auto i : matchView.getRoundCirclesP2()){
            app.draw(i);
        }

       matchView.actualiseRoundCircles();

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
