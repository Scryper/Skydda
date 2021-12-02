#include "GameScreenTimer.h"

GameScreenTimer::GameScreenTimer()
{
    //ctor
}

GameScreenTimer::~GameScreenTimer()
{
    //dtor
}

GameScreenTimer::GameScreenTimer(const GameScreenTimer& other)
{
    //copy ctor
}

int GameScreenTimer::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
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

    while(app.isOpen()) {
        const int SCRWIDTH = app.getSize().x;
        //const int SCRHEIGHT = app.getSize().y -200;
        // --- TextTimer ---
        sf::Time timer = clockTimer.getElapsedTime();
        //int time = timer.asSeconds();
//        sf::Text timeTxt;

        std::stringstream ss;
        ss << (int)gameTimer.getCountDown();
        Position position(SCRWIDTH/2.0f, 50.f);
        sf::Text timeTxt = TextInitializer::createText(ss.str(), position);

//        timeTxt.setString(ss.str().c_str());
//        timeTxt.setPosition(800., 0.);
        timeTxt.setFillColor(sf::Color::Red);
        timeTxt.setFont(font);
        timeTxt.setCharacterSize(80);
        sf::FloatRect textRectTime = timeTxt.getLocalBounds();
        timeTxt.setOrigin(textRectTime.width/2,textRectTime.height/2);


        sf::RectangleShape rectangle(sf::Vector2f(300.0f,100.0f));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(SCRWIDTH/2.0f,70.f);
        sf::FloatRect textRectRect = rectangle.getLocalBounds();
        rectangle.setOrigin(textRectRect.width/2,textRectRect.height/2);

        // --- TextTimer ---

        sf::Time timerAnimation = clockTimerAnimation.getElapsedTime();
        deltaTime = clock.restart().asMilliseconds();

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

        if(gameTimer.getPlayerWin() == 0) {
            if(gameTimer.getPlayer1().getHealth() == 0) {

                gameTimer.incrementRoundWinP2();
                gameTimer.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                gameTimer.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(gameTimer.getPlayerWin() == 0) {
                    gameTimer.getPlayer1().setHealth(100.f);
                    gameTimer.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }else if(gameTimer.getPlayer2().getHealth() == 0) {
                gameTimer.incrementRoundWinP1();
                gameTimer.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                gameTimer.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(gameTimer.getPlayerWin() == 0) {
                    gameTimer.getPlayer1().setHealth(100.f);
                    gameTimer.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }
            else{
                movePlayers(deltaTime, false);
            }
        } else {
            gameTimer.win();
        }

        app.clear();

        // Draw elements
        app.draw(backgroundSprite);
        app.draw(playerViewP1.getSprite());
        app.draw(playerViewP2.getSprite());

        for(auto platform : map_.getPlatforms()) app.draw(platform.getSprite());

        app.draw(healthBarViewP1.getHealthBarOut());
        app.draw(healthBarViewP1.getHealthBarIn());

        app.draw(healthBarViewP2.getHealthBarOut());
        app.draw(healthBarViewP2.getHealthBarIn());

        app.draw(namePlayerP1);
        app.draw(namePlayerP2);
        app.draw(textAnimation);

        app.draw(rectangle);
        app.draw(timeTxt);

        //for borders' debug
//        for(PlatformView border : map_.getBorders()) app.draw(border.getSprite());

        app.display();

        gameTimer.decrementCountDown();

    }

    return -1;
}

sf::Text GameScreenTimer::displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app) {

    timeAnimation = timerAnimation.asSeconds();
    int time = timer.asSeconds();
    bool isPlayerDead = gameTimer.getPlayer1().getHealth() == 0 || gameTimer.getPlayer2().getHealth() == 0;
    bool isPlayerWin = gameTimer.getPlayerWin() != 0;
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
            textWin << ( (gameTimer.getPlayerWin() == 1)? (GameScreen::playerName1):(GameScreen::playerName2) ) << " Win !";
            return displayTextAnimation(app, textWin.str());
    }
    // Lance l'animation de K.O.
    else if(startAnimationKO && timeAnimation < 3) return displayTextAnimation(app, "K.O. !");

    resetAnimationAndClock();
    return displayTextAnimation(app, "");
}

void GameScreenTimer::setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app) {

    textAnimation = displayAnimations(timer, timerAnimation, app);

    textAnimation.setFont(font);
    textAnimation.setCharacterSize(140);

    sf::FloatRect textRect = textAnimation.getLocalBounds();
    textAnimation.setOrigin(textRect.width/2,textRect.height/2);
}
