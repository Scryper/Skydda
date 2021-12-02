#include "GameScreenRound.h"

GameScreenRound::GameScreenRound()
{
    //ctor
}

GameScreenRound::~GameScreenRound()
{
    //dtor
}

GameScreenRound::GameScreenRound(const GameScreenRound& other)
{
    //copy ctor
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

    gameRound = GameRound(playerViewP1.getPlayer(), playerViewP2.getPlayer());
    clearRoundCircles();
    sf::Clock clockTest;
    clockTest.restart().asMilliseconds();

    while(app.isOpen()) {

        sf::Time timer = clockTimer.getElapsedTime();
        sf::Time timerAnimation = clockTimerAnimation.getElapsedTime();
        deltaTime = clock.restart().asMilliseconds();

        if(clockTest.getElapsedTime().asMilliseconds() >= 2000 && clockTest.getElapsedTime().asMilliseconds() <= 2016) {
            SoundLoader::playRandomSound();
        }

        while(app.pollEvent(event)) {
            if(event.type == sf::Event::Closed) return -1;

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) return 0;
            }
        }

        //verif l'input
        //attaquer si poss
        //vérif et update les manches la vie et le reste -> va update la position SI MORT
        //update la position en fonction de cette nouvelle position

        playerUpdate();

        healthBarViewP1.actualiseSizeHealthBarIn(playerViewP1.getPlayer().getHealth());
        healthBarViewP2.actualiseSizeHealthBarIn(playerViewP2.getPlayer().getHealth());



        setAnimationText(timer, timerAnimation, app);

        if(gameRound.getPlayerWin() == 0) {
            if(gameRound.getPlayer1().getHealth() == 0) {

                gameRound.incrementRoundWinP2();
                gameRound.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                gameRound.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(gameRound.getPlayerWin() == 0) {
                    gameRound.getPlayer1().setHealth(100.f);
                    gameRound.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }else if(gameRound.getPlayer2().getHealth() == 0) {
                gameRound.incrementRoundWinP1();
                gameRound.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                gameRound.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(gameRound.getPlayerWin() == 0) {
                    gameRound.getPlayer1().setHealth(100.f);
                    gameRound.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }
            else{
                movePlayers(deltaTime, false);
            }
        } else {
            gameRound.win();
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);
        app.draw(playerViewP1.getSprite());
        app.draw(playerViewP2.getSprite());

        for(auto platform : map_.getPlatforms()) app.draw(platform.getSprite());

        for(auto circle : getRoundCirclesP1()) app.draw(circle);

        for(auto circle : getRoundCirclesP2()) app.draw(circle);

        actualiseRoundCircles();
        app.draw(healthBarViewP1.getHealthBarOut());
        app.draw(healthBarViewP1.getHealthBarIn());

        app.draw(healthBarViewP2.getHealthBarOut());
        app.draw(healthBarViewP2.getHealthBarIn());

        app.draw(namePlayerP1);
        app.draw(namePlayerP2);
        app.draw(textAnimation);

        //for borders' debug
//        for(PlatformView border : map_.getBorders()) app.draw(border.getSprite());

        app.display();
    }

    return -1;
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

void GameScreenRound::initHealthBars() {
    // Create HealthBar
    Position posHealthBarP1(50.f, 50.f);
    Position posHealthBarP2(1550.f, 50.f);

    healthBarViewP1 = createHealthBar(playerViewP1.getPlayer(), posHealthBarP1);
    healthBarViewP2 = createHealthBar(playerViewP2.getPlayer(), posHealthBarP2);

    // Create posNamePlayer
    Position posNamePlayerP1(50.f, 80.f);
    Position posNamePlayerP2(1550.f, 80.f);
    namePlayerP1 = healthBarViewP1.createNamePlayer(playerViewP1.getPlayer(), posNamePlayerP1);
    namePlayerP2 = healthBarViewP2.createNamePlayer(playerViewP2.getPlayer(), posNamePlayerP2);

    font.loadFromFile("resources/fonts/glitch.otf");

    std::vector<sf::Text*> texts;
    texts.push_back(&namePlayerP1);
    texts.push_back(&namePlayerP2);

    TextInitializer::initFont(texts, &font);

    createRoundCircles();
}

void GameScreenRound::clearRoundCircles() {
    roundCirclesP1[0].setFillColor(sf::Color::Transparent);
    roundCirclesP1[1].setFillColor(sf::Color::Transparent);
    roundCirclesP1[2].setFillColor(sf::Color::Transparent);

    roundCirclesP2[0].setFillColor(sf::Color::Transparent);
    roundCirclesP2[1].setFillColor(sf::Color::Transparent);
    roundCirclesP2[2].setFillColor(sf::Color::Transparent);
}

GameRound& GameScreenRound::getGameRound() {
    return gameRound;
}

sf::Text GameScreenRound::displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app) {

    timeAnimation = timerAnimation.asSeconds();
    int time = timer.asSeconds();
    bool isPlayerDead = gameRound.getPlayer1().getHealth() == 0 || gameRound.getPlayer2().getHealth() == 0;
    bool isPlayerWin = gameRound.getPlayerWin() != 0;
    std::stringstream textWin;

    // Lance une animation x seconde après le lancement de la partie
    switch(time) {
        case 3: return displayTextAnimation(app, "Round 1 !");
        case 5: return displayTextAnimation(app, "Ready ?");
        case 7: return displayTextAnimation(app, "Fight !");
    }

    if(isPlayerWin) startAnimationWin = true;
    else if(isPlayerDead && !isPlayerWin) startAnimationKO = true;
    if((isPlayerWin || isPlayerDead ) && !isClockAlreadyRestarted) startClock();

    // Lance l'animation de victoire
    if(startAnimationWin) {
            textWin << ( (gameRound.getPlayerWin() == 1) ? (GameScreen::playerName1):(GameScreen::playerName2) ) << " Win !";
            return displayTextAnimation(app, textWin.str());
    }
    // Lance l'animation de K.O.
    else if(startAnimationKO && timeAnimation < 3) return displayTextAnimation(app, "K.O. !");

    resetAnimationAndClock();
    return displayTextAnimation(app, "");
}

void GameScreenRound::setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app) {

    textAnimation = displayAnimations(timer, timerAnimation, app);

    textAnimation.setFont(font);
    textAnimation.setCharacterSize(150);

    sf::FloatRect textRect = textAnimation.getLocalBounds();
    textAnimation.setOrigin(textRect.width/2,textRect.height/2);
}

