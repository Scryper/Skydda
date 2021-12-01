#include "GameScreen.h"

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

sf::Text GameScreen::displayTextAnimation(sf::RenderWindow &app, std::string textStr) {
    const int SCRWIDTH = app.getSize().x;
    const int SCRHEIGHT = app.getSize().y -200;

    Position position(SCRWIDTH/2.0f, SCRHEIGHT/2.0f);
    sf::Text textAnimation = TextInitializer::createText(textStr, position);

    textAnimation.setFillColor(sf::Color::Red);
    textAnimation.setOutlineColor(sf::Color::Black);
    textAnimation.setOutlineThickness(4);

    return textAnimation;
}

void GameScreen::resetAnimationAndClock() {
    startAnimationKO = false;
    isClockAlreadyRestarted = false;
}

void GameScreen::startClock() {
    clockTimerAnimation.restart();
    isClockAlreadyRestarted = true;
    timeAnimation = 0;
}
