#include "GameScreenRound.h"

GameScreenRound::GameScreenRound() {}

GameScreenRound::~GameScreenRound() {}

GameScreenRound::GameScreenRound(const GameScreenRound& other) {}

GameScreenRound& GameScreenRound::operator=(const GameScreenRound& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

int GameScreenRound::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    playerName1 = data[0];
    spriteSheet1 = data[1];
    playerName2 = data[2];
    spriteSheet2 = data[3];
    mapSeed = seed;

    sf::Event event;

    float deltaTime;
    sf::Clock clock;
    sf::Clock clockTimer;

    position = getScreenCenter(&app);

    initSprites();
    initTextures();
    initVectors();
    initMap();
    initPlayers();
    initHealthBars();
    createRoundCircles();

    gameRound = GameRound(playerViewP1.getPlayer(), playerViewP2.getPlayer());
    clearRoundCircles();
    sf::Clock clockTest;
    clockTest.restart().asMilliseconds();

    playerViewP1.getPlayer().setState(standby,true);
    playerViewP2.getPlayer().setState(standby,true);

    textRejouer = TextInitializer::createText("Play again", 950.f, 380.f);
    textSelectPerso = TextInitializer::createText("Select characters", 950.f, 510.f);
    textMenuPrincipal = TextInitializer::createText("Main menu", 950.f, 640.f);

    while(app.isOpen()) {
        sf::Time timer = clockTimer.getElapsedTime();
        sf::Time timerAnimation = clockTimerAnimation.getElapsedTime();
        deltaTime = clock.restart().asMilliseconds();

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }
            /// Button Rejouer
            if(buttonRejouer.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    return 3;
                } else {
                    textRejouer.setFillColor(sf::Color::Green);
                }
            }
            else {
                textRejouer.setFillColor(sf::Color::White);
            }

            /// Button selectPerso
            if(buttonSelectPerso.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) {
                    return 1;
                } else {
                    textSelectPerso.setFillColor(sf::Color::Green);
                }
            }
            else {

                textSelectPerso.setFillColor(sf::Color::White);
            }

            /// Button menuPrincipal
            if(buttonMenuPrincipal.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed){
                    return 0;
                } else {
                    textMenuPrincipal.setFillColor(sf::Color::Green);
                }
            }
            else {
                textMenuPrincipal.setFillColor(sf::Color::White);
            }
        }

            //verif l'input
            //attaquer si poss
            //vérif et update les manches la vie et le reste -> va update la position SI MORT
            //update la position en fonction de cette nouvelle position
            healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
            healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());

            managementWin(deltaTime, &gameRound, timer, timerAnimation, &app);
            app.clear();

            setMenuText(&app);
            drawAll(&app);

        }

    return -1;
}

void GameScreenRound::setMenuText(sf::RenderWindow *app) {
    sf::FloatRect textRect;
    mousePosition = getMousePosition(app);

    rectangle.setSize(sf::Vector2f(850.f, 450.f));
    rectangle.setPosition(525.f,290.f);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);

    textRejouer.setFont(font);
    textRejouer.setCharacterSize(40);

    textSelectPerso.setFont(font);
    textSelectPerso.setCharacterSize(40);

    textMenuPrincipal.setFont(font);
    textMenuPrincipal.setCharacterSize(40);

    // Center texts
    textRect = textRejouer.getLocalBounds();
    textRejouer.setOrigin(textRect.width/2,textRect.height/2);
    textRect = textSelectPerso.getLocalBounds();
    textSelectPerso.setOrigin(textRect.width/2,textRect.height/2);
    textRect = textMenuPrincipal.getLocalBounds();
    textMenuPrincipal.setOrigin(textRect.width/2,textRect.height/2);

    Position positionButtonRejouer(950.f, 385.f);
    buttonRejouer = initSprite(1.f, 1.6f, "resources/images/buttons/button.png", positionButtonRejouer, &textureButton);

    Position positionSelectPerso(950.f, 512.f);
    buttonSelectPerso = initSprite(2.75f, 1.6f, "resources/images/buttons/button.png", positionSelectPerso, &textureButton);

    Position positionMenuPrincipal(950.f, 643.f);
    buttonMenuPrincipal = initSprite(2.75f, 1.6f, "resources/images/buttons/button.png", positionMenuPrincipal, &textureButton);

}

void GameScreenRound::drawAll(sf::RenderWindow *app) {
    app->draw(backgroundSprite);
    app->draw(playerViewP1.getSprite());
    app->draw(playerViewP2.getSprite());

    for(auto platform : map_.getPlatforms()) app->draw(platform.getSprite());
//    for(auto platform : map_.getBorders()) app->draw(platform.getSprite());
    for(auto circle : getRoundCirclesP1()) app->draw(circle);
    for(auto circle : getRoundCirclesP2()) app->draw(circle);

    actualiseRoundCircles();
    app->draw(healthBarViewP1.getHealthBarOut());
    app->draw(healthBarViewP1.getHealthBarIn());
    app->draw(healthBarViewP2.getHealthBarOut());
    app->draw(healthBarViewP2.getHealthBarIn());
    app->draw(namePlayerP1);
    app->draw(namePlayerP2);
    app->draw(textAnimation);
    if(startMenu) {
        app->draw(rectangle);
        app->draw(buttonRejouer);
        app->draw(textRejouer);
        app->draw(buttonSelectPerso);
        app->draw(textSelectPerso);
        app->draw(buttonMenuPrincipal);
        app->draw(textMenuPrincipal);
    }
    app->display();
}



std::vector<sf::CircleShape> GameScreenRound::getRoundCirclesP1() {
    return roundCirclesP1;
}

std::vector<sf::CircleShape> GameScreenRound::getRoundCirclesP2() {
    return roundCirclesP2;
}

void GameScreenRound::createRoundCircles() {
    Position posP1(60.f, 135.f);
    Position posP2(1360.f, 135.f);

    sf::CircleShape roundCircle(10);
    roundCircle.setFillColor(sf::Color::Transparent);
    roundCircle.setOutlineThickness(3);
    roundCircle.setOutlineColor(sf::Color::Black);

    // P1
    roundCircle.setPosition(posP1.getX(), posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    roundCircle.setPosition(posP1.getX() + 50, posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    roundCircle.setPosition(posP1.getX() + 100, posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    // P2
    roundCircle.setPosition(posP2.getX() + 200, posP2.getY());
    roundCirclesP2.push_back(roundCircle);

    roundCircle.setPosition(posP2.getX() + 250, posP2.getY());
    roundCirclesP2.push_back(roundCircle);

    roundCircle.setPosition(posP2.getX() + 300, posP2.getY());
    roundCirclesP2.push_back(roundCircle);
}

void GameScreenRound::actualiseRoundCircles() {
    switch(gameRound.getRoundWinP1()) {
        case 1:
            roundCirclesP1[0].setFillColor(sf::Color::White);
            break;
        case 2:
            roundCirclesP1[1].setFillColor(sf::Color::White);
            break;
        case 3:
            roundCirclesP1[2].setFillColor(sf::Color::White);
            break;
    }
    switch(gameRound.getRoundWinP2()) {
        case 1:
            roundCirclesP2[0].setFillColor(sf::Color::White);
            break;
        case 2:
            roundCirclesP2[1].setFillColor(sf::Color::White);
            break;
        case 3:
            roundCirclesP2[2].setFillColor(sf::Color::White);
            break;
    }
}

void GameScreenRound::clearRoundCircles() {
    roundCirclesP1[0].setFillColor(sf::Color::Transparent);
    roundCirclesP1[1].setFillColor(sf::Color::Transparent);
    roundCirclesP1[2].setFillColor(sf::Color::Transparent);

    roundCirclesP2[0].setFillColor(sf::Color::Transparent);
    roundCirclesP2[1].setFillColor(sf::Color::Transparent);
    roundCirclesP2[2].setFillColor(sf::Color::Transparent);
}


void GameScreenRound::initPlayers() {
    switch(mapSeed) {
        case 1:
            positionP1 = Position(position.getX() - 300, position.getY()+335);
            positionP2 = Position(position.getX() + 300, position.getY()+335);
            break;
        case 2:
            positionP1 = Position(position.getX() - 300, position.getY()+335);
            positionP2 = Position(position.getX() + 300, position.getY()+335);
            break;
        case 3:
            positionP1 = Position(position.getX() - 300, position.getY()+335);
            positionP2 = Position(position.getX() + 300, position.getY()+335);
            break;
        default:
            positionP1 = Position(position.getX() - 300, position.getY() + 335);
            positionP2 = Position(position.getX() + 300, position.getY() + 335);
            break;
    }

    CoupleFloat scaleP1(.5f, .5f);
    CoupleFloat scaleP2(.5f, .5f);
    CoupleFloat textureCharacter(327.f, 273.f);

    // Load sprite of player
    float atk = 15.f;
    float health = 100.f;
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.7f, 1.f);
    CoupleFloat maxSpeed(11.f, 30.f);
    float jumpHeight = 24.f;
    CoupleFloat sizeCouple(scaleP1.getX(), scaleP1.getY());
    CoupleFloat sizeOfSprite(sizeCouple);

    CoupleFloat centerOfSprite(textureCharacter.getX(), textureCharacter.getY());

    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    PlayerBuilder builder;
    Player playerFromBuilder = builder.reset()
                                    ->withName(playerName1)
                                    ->withAttack(atk)
                                    ->withHealth(health)
                                    ->withPosition(positionP1)
                                    ->withMovement(movement)
                                    ->build();

    PlayerViewBuilder viewBuilder;
    playerViewP1 = viewBuilder.reset()
                        ->withSprite(sizeCouple, centerOfSprite, spriteSheet1, positionP1, texturePlayerP1)
                        ->withPlayer(playerFromBuilder)
                        ->withKeys(sf::Keyboard::Z,
                                    sf::Keyboard::Q,
                                    sf::Keyboard::D,
                                    sf::Keyboard::C,
                                    sf::Keyboard::S,
                                    sf::Keyboard::V)
                        ->withLooksRight(true)
                        ->build();

    playerFromBuilder = builder.reset()
                ->withName(playerName2)
                ->withAttack(atk)
                ->withHealth(health)
                ->withPosition(positionP2)
                ->withMovement(movement)
                ->build();

    playerViewP2 = viewBuilder.reset()
                    ->withSprite(sizeCouple, centerOfSprite, spriteSheet2, positionP2, texturePlayerP2)
                    ->withPlayer(playerFromBuilder)
                    ->withKeys(sf::Keyboard::Up,
                                sf::Keyboard::Left,
                                sf::Keyboard::Right,
                                sf::Keyboard::L,
                                sf::Keyboard::Down,
                                sf::Keyboard::M)
                    ->withLooksRight(false)
                    ->build();
    playerViewP2.flipSprite();
}
