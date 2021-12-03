#include "GameScreenTimer.h"

GameScreenTimer::GameScreenTimer() {
    //ctor
}

GameScreenTimer::~GameScreenTimer() {
    //dtor
}

GameScreenTimer::GameScreenTimer(const GameScreenTimer& other){
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
        const int SCRWIDTH = app.getSize().x; //const int SCRHEIGHT = app.getSize().y -200;
        sf::Time timer = clockTimer.getElapsedTime();

        // --- TextTimer ---
        std::stringstream ss;
        ss << (int)gameTimer.getCountDown();
        Position position(SCRWIDTH/2.0f, 50.f);
        sf::Text timeTxt = TextInitializer::createText(ss.str(), position);

        setTextTime(&timeTxt);

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

        setAnimationText(timer, timerAnimation, &app, &gameTimer);

        managementWin(deltaTime, &gameTimer);

        app.clear();

        drawAll(&app, &timeTxt);

        gameTimer.decrementCountDown();

    }

    return -1;
}

void GameScreenTimer::setTextTime(sf::Text *timeTxt) {
    timeTxt->setFillColor(sf::Color::Red);
    timeTxt->setFont(font);
    timeTxt->setCharacterSize(80);
    sf::FloatRect textRectTime = timeTxt->getLocalBounds();
    timeTxt->setOrigin(textRectTime.width/2,textRectTime.height/2);
}

void GameScreenTimer::drawAll(sf::RenderWindow *app, sf::Text *timeTxt) {
    app->draw(backgroundSprite);
    app->draw(playerViewP1.getSprite());
    app->draw(playerViewP2.getSprite());

    for(auto platform : map_.getPlatforms()) app->draw(platform.getSprite());

    app->draw(healthBarViewP1.getHealthBarOut());
    app->draw(healthBarViewP1.getHealthBarIn());
    app->draw(healthBarViewP2.getHealthBarOut());
    app->draw(healthBarViewP2.getHealthBarIn());
    app->draw(namePlayerP1);
    app->draw(namePlayerP2);
    app->draw(textAnimation);
    app->draw(*timeTxt);

    app->display();
}
