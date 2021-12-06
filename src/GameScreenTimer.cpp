#include "GameScreenTimer.h"

GameScreenTimer::GameScreenTimer() {}

GameScreenTimer::~GameScreenTimer() {}

GameScreenTimer::GameScreenTimer(const GameScreenTimer& other){}

GameScreenTimer& GameScreenTimer::operator=(const GameScreenTimer& rhs) {
    if (this == &rhs) return *this;
    return *this;
}

// Run the game in timer mode
int GameScreenTimer::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
    // extract the data
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

    gameTimer = GameTimer(playerViewP1.getPlayer(), playerViewP2.getPlayer());
    playerViewP1.getPlayer().setState(standby,true);
    playerViewP2.getPlayer().setState(standby,true);

    // Init menu texts
    textPlayAgain = TextInitializer::createText("Play again", 950.f, 380.f);
    textSelectCharacters = TextInitializer::createText("Select characters", 950.f, 510.f);
    textMainMenu = TextInitializer::createText("Main menu", 950.f, 640.f);

    while(app.isOpen()) {
        const int SCRWIDTH = app.getSize().x;
        sf::Time timer = clockTimer.getElapsedTime();

        setTextTime(SCRWIDTH);
        setTextRoundWin();

        sf::Time timerAnimation = clockTimerAnimation.getElapsedTime();
        deltaTime = clock.restart().asMilliseconds();

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }
            /// Button PlayAgain
            if(buttonPlayAgain.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) return 4;
                else {
                    textPlayAgain.setFillColor(sf::Color::Green);
                }
            }
            else {
                textPlayAgain.setFillColor(sf::Color::White);
            }

            /// Button SelectCharacters
            if(buttonSelectCharacters.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) return 1;
                else {
                    textSelectCharacters.setFillColor(sf::Color::Green);
                }
            }
            else {
                textSelectCharacters.setFillColor(sf::Color::White);
            }

            /// Button MainMenu
            if(buttonMainMenu.getGlobalBounds().contains(mousePosition)) {
                if(event.type == sf::Event::MouseButtonPressed) return 0;
                else {
                    textMainMenu.setFillColor(sf::Color::Green);
                }
            }
            else {
                textMainMenu.setFillColor(sf::Color::White);
            }
        }

        //verif l'input
        // attack if possible
        // verify and update rounds, health,... -> update position if dead
        healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
        healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());

        managementWin(deltaTime, &gameTimer,timer, timerAnimation, &app);
        app.clear();

        setMenuText(&app);
        drawAll(&app);

        if(timer.asSeconds() > timeAnimFight+1) {
            gameTimer.decrementCountDown();
        }
    }
    return -1;
}

// create the "window" of end games
void GameScreenTimer::setTextRoundWin() {
    std::stringstream ss1;
    ss1 << gameTimer.getPlayer1().getPoints();
    ss1 << " points";
    positionRoundWinTxtP1.setX(150.f);
    positionRoundWinTxtP1.setY(140.f);
    RoundWinTxtP1 = TextInitializer::createText(ss1.str(), positionRoundWinTxtP1);

    RoundWinTxtP1.setFillColor(sf::Color::Red);
    RoundWinTxtP1.setFont(font);
    RoundWinTxtP1.setCharacterSize(30);
    sf::FloatRect textRectTime1 = RoundWinTxtP1.getLocalBounds();
    RoundWinTxtP1.setOrigin(textRectTime1.width/2,textRectTime1.height/2);

    std::stringstream ss2;
    ss2 << gameTimer.getPlayer2().getPoints();
    ss2 << " points";
    positionRoundWinTxtP2.setX(1650.f);
    positionRoundWinTxtP2.setY(140.f);
    RoundWinTxtP2 = TextInitializer::createText(ss2.str(), positionRoundWinTxtP2);

    RoundWinTxtP2.setFillColor(sf::Color::Red);
    RoundWinTxtP2.setFont(font);
    RoundWinTxtP2.setCharacterSize(30);
    sf::FloatRect textRectTime2 = RoundWinTxtP2.getLocalBounds();
    RoundWinTxtP2.setOrigin(textRectTime2.width/2,textRectTime2.height/2);

}

// create the "window" of end games
void GameScreenTimer::setMenuText(sf::RenderWindow *app) {
    sf::FloatRect textRect;
    mousePosition = getMousePosition(app);

    rectangle.setSize(sf::Vector2f(850.f, 450.f));
    rectangle.setPosition(525.f,290.f);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(4);

    textPlayAgain.setFont(font);
    textPlayAgain.setCharacterSize(40);

    textSelectCharacters.setFont(font);
    textSelectCharacters.setCharacterSize(40);

    textMainMenu.setFont(font);
    textMainMenu.setCharacterSize(40);

    // Center texts
    textRect = textPlayAgain.getLocalBounds();
    textPlayAgain.setOrigin(textRect.width/2,textRect.height/2);
    textRect = textSelectCharacters.getLocalBounds();
    textSelectCharacters.setOrigin(textRect.width/2,textRect.height/2);
    textRect = textMainMenu.getLocalBounds();
    textMainMenu.setOrigin(textRect.width/2,textRect.height/2);

    Position positionButtonRejouer(950.f, 385.f);
    buttonPlayAgain = initSprite(2.75f, 1.6f, "resources/images/buttons/button.png", positionButtonRejouer, &textureButton);

    Position positionSelectPerso(950.f, 512.f);
    buttonSelectCharacters = initSprite(2.75f, 1.6f, "resources/images/buttons/button.png", positionSelectPerso, &textureButton);

    Position positionMenuPrincipal(950.f, 643.f);
    buttonMainMenu = initSprite(2.75f, 1.6f, "resources/images/buttons/button.png", positionMenuPrincipal, &textureButton);
}

// load timeTxt
void GameScreenTimer::setTextTime(int SCRWIDTH) {
    std::stringstream ss;
    ss << (int)gameTimer.getCountDown();
    positionTimeTxt.setX(SCRWIDTH/2.0f);
    positionTimeTxt.setY(50.f);
    timeTxt = TextInitializer::createText(ss.str(), positionTimeTxt);

    timeTxt.setFillColor(sf::Color::Red);
    timeTxt.setFont(font);
    timeTxt.setCharacterSize(80);
    sf::FloatRect textRectTime = timeTxt.getLocalBounds();
    timeTxt.setOrigin(textRectTime.width/2,textRectTime.height/2);
}

void GameScreenTimer::drawAll(sf::RenderWindow *app) {
    app->draw(backgroundSprite);
    app->draw(playerViewP1.getSprite());
    app->draw(playerViewP2.getSprite());

    for(auto platform : map_.getPlatforms()) app->draw(platform.getSprite());

    app->draw(namePlayerP1);
    app->draw(namePlayerP2);
    app->draw(textAnimation);
    app->draw(timeTxt);
    app->draw(RoundWinTxtP1);
    app->draw(RoundWinTxtP2);

    if(startMenu) {
        app->draw(rectangle);
        app->draw(buttonPlayAgain);
        app->draw(textPlayAgain);
        app->draw(buttonSelectCharacters);
        app->draw(textSelectCharacters);
        app->draw(buttonMainMenu);
        app->draw(textMainMenu);
    }
    app->display();
}

// creates the player, positions, view, textures,...
void GameScreenTimer::initPlayers() {
    positionP1 = Position(position.getX() - 300, position.getY()+335);
    positionP2 = Position(position.getX() + 300, position.getY()+335);

    CoupleFloat scaleP1(.5f, .5f);
    CoupleFloat scaleP2(.5f, .5f);
    CoupleFloat textureCharacter(327.f, 273.f);

    // Load sprite of player
    float atk = 4.f;
    float health = 10000.f;
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.7f, 1.f);
    CoupleFloat maxSpeed(11.f, 30.f);
    float jumpHeight = 24.f;
    int initialPoints = 0;
    CoupleFloat sizeCouple(scaleP1.getX(), scaleP1.getY());
    CoupleFloat sizeOfSprite(sizeCouple);

    CoupleFloat centerOfSprite(textureCharacter.getX(), textureCharacter.getY());

    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    // create the player and their view with the builders
    PlayerBuilder builder;
    Player playerFromBuilder = builder.reset()
                                    ->withName(playerName1)
                                    ->withAttack(atk)
                                    ->withHealth(health)
                                    ->withPosition(positionP1)
                                    ->withMovement(movement)
                                    ->withPoints(initialPoints)
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
                ->withPoints(initialPoints)
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
