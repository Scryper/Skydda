#include "GameScreen.h"

int GameScreen::run(sf::RenderWindow &app, std::vector<std::string> data, int seed) {
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

    game = Game(playerViewP1.getPlayer(), playerViewP2.getPlayer());
    clearRoundCircles();



    while(app.isOpen()) {


        sf::Time timer = clockTimer.getElapsedTime();
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

        if(game.getPlayerWin() == 0) {
            if(game.getPlayer1().getHealth() == 0) {
                game.incrementRoundWinP2();
                game.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                game.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(game.getPlayerWin() == 0) {
                    game.getPlayer1().setHealth(100.f);
                    game.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }else if(game.getPlayer2().getHealth() == 0) {
                game.incrementRoundWinP1();
                game.getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
                game.getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
                if(game.getPlayerWin() == 0) {
                    game.getPlayer1().setHealth(100.f);
                    game.getPlayer2().setHealth(100.f);
                }
                movePlayers(deltaTime, true);
            }
            else{
                movePlayers(deltaTime, false);
            }
        } else {
            game.win();
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

        setAnimationText(timer, app);

        app.draw(textAnimation);

        //for borders' debug
//        for(PlatformView border : map_.getBorders()) app.draw(border.getSprite());

        app.display();
    }

    return -1;
}

Game& GameScreen::getGame() {
    return game;
}

void GameScreen::createRoundCircles() {
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

void GameScreen::actualiseRoundCircles() {
    switch(game.getRoundWinP1()) {
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
    switch(game.getRoundWinP2()) {
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

void GameScreen::clearRoundCircles() {
    roundCirclesP1[0].setFillColor(sf::Color::Transparent);
    roundCirclesP1[1].setFillColor(sf::Color::Transparent);
    roundCirclesP1[2].setFillColor(sf::Color::Transparent);

    roundCirclesP2[0].setFillColor(sf::Color::Transparent);
    roundCirclesP2[1].setFillColor(sf::Color::Transparent);
    roundCirclesP2[2].setFillColor(sf::Color::Transparent);
}

std::vector<sf::CircleShape> GameScreen::getRoundCirclesP1() {
    return roundCirclesP1;
}

std::vector<sf::CircleShape> GameScreen::getRoundCirclesP2() {
    return roundCirclesP2;
}

void GameScreen::initPlayers() {

    switch(mapSeed) {
    case 1:
        positionP1 = Position(position.getX() - 500, position.getY()+300);
        positionP2 = Position(position.getX() + 500, position.getY()+300);
        break;
    case 2:
        positionP1 = Position(position.getX() - 500, position.getY());
        positionP2 = Position(position.getX() + 500, position.getY());
        break;
    default:
        positionP1 = Position(position.getX() - 500, position.getY());
        positionP2 = Position(position.getX() + 500, position.getY());
        break;
    }

    CoupleFloat scaleP1(.5f, .5f);
    CoupleFloat scaleP2(.5f, .5f);
    CoupleFloat textureCharacter(327.f, 273.f);

    // Load sprite of player
    playerViewP1 = createPlayer(scaleP1.getX(),
                                scaleP1.getY(),
                                textureCharacter.getX(),
                                textureCharacter.getY(),
                                spriteSheet1,
                                positionP1,
                                &texturePlayerP1,
                                sf::Keyboard::Z,
                                sf::Keyboard::Q,
                                sf::Keyboard::D,
                                sf::Keyboard::S,
                                sf::Keyboard::LShift,
                                true,
                                playerName1);

    playerViewP2 = createPlayer(scaleP2.getX(),
                                scaleP2.getY(),
                                textureCharacter.getX(),
                                textureCharacter.getY(),
                                spriteSheet2,
                                positionP2,
                                &texturePlayerP2,
                                sf::Keyboard::Up,
                                sf::Keyboard::Left,
                                sf::Keyboard::Right,
                                sf::Keyboard::Down,
                                sf::Keyboard::RShift,
                                false,
                                playerName2);
    playerViewP2.flipSprite();
}

void GameScreen::initMap() {
    //loading the map
    Map mapModel(mapSeed);
    map_ = MapView(mapModel, textures);

    //get all the platforms from the map
    platforms = map_.getAllCollisions();
}

void GameScreen::initSprites() {
    backgroundSprite = initSprite(1.f, 1.f, "resources/images/background/background_battle.png", position, &textureBackground);
}

void GameScreen::initTextures() {
    texturePlatformGround.loadFromFile("resources/images/platforms/platform_ground.png");
    texturePlatformLong.loadFromFile("resources/images/platforms/platform_long.png");
    texturePlatformSmall.loadFromFile("resources/images/platforms/platform_small.png");
    texturePlatformTiny.loadFromFile("resources/images/platforms/platform_tiny.png");
}

void GameScreen::initVectors() {
    textures.push_back(&texturePlatformGround);
    textures.push_back(&texturePlatformLong);
    textures.push_back(&texturePlatformSmall);
    textures.push_back(&texturePlatformTiny);
}

void GameScreen::setAnimationText(sf::Time timer,sf::RenderWindow &app) {

    textAnimation = displayAnimations(timer, app);

    textAnimation.setFont(font);
    textAnimation.setCharacterSize(200);

    sf::FloatRect textRect = textAnimation.getLocalBounds();
    textAnimation.setOrigin(textRect.width/2,textRect.height/2);
}

void GameScreen::initHealthBars() {
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

void GameScreen::movePlayers(float deltaTime, bool noTP) {
    playerViewP1.movePlayer(playerViewP1.computeCoupleMovement(),
                            directionCollisions(playerViewP1, platforms), noTP);

    playerViewP2.movePlayer(playerViewP2.computeCoupleMovement(),
                            directionCollisions(playerViewP2, platforms), noTP);
}

void GameScreen::playerUpdate(){
    playerViewP1.updateState(playerViewP2);
    playerViewP2.updateState(playerViewP1);
    playerViewP1.animate();
    playerViewP2.animate();
}
