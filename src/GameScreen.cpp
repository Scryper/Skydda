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
                                sf::Keyboard::C,
                                sf::Keyboard::S,
                                sf::Keyboard::V,
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
                                sf::Keyboard::L,
                                sf::Keyboard::Down,
                                sf::Keyboard::M,
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
    std::string path = "";
    switch(mapSeed) {
        case 1:
            path = "resources/images/background/background_battle_1.png";
            break;
        case 2:
            path = "resources/images/background/background_battle_2.png";
            break;
        case 3:
            path = "resources/images/background/background_battle_3.png";
            break;
        default:
            path = "resources/images/background/background_battle_1.png";
            break;
    }
    backgroundSprite = initSprite(1.f, 1.f, path, position, &textureBackground);
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

void GameScreen::movePlayers(float deltaTime) {
    playerViewP1.computeFrame(directionCollisions(playerViewP1, platforms),playerViewP2);
    playerViewP2.computeFrame(directionCollisions(playerViewP2, platforms),playerViewP1);
}

sf::Text GameScreen::displayTextAnimation(sf::RenderWindow *app, std::string textStr) {
    const int SCRWIDTH = app->getSize().x;
    const int SCRHEIGHT = app->getSize().y -200;

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

sf::Text GameScreen::displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app, Game* modeJeu) {

    timeAnimation = timerAnimation.asSeconds();
    int time = timer.asSeconds();
    bool isPlayerDead = modeJeu->getPlayer1().getHealth() == 0 || modeJeu->getPlayer2().getHealth() == 0;
    bool isPlayerStandBy = modeJeu->getPlayer1().getState(standby) == 1 || modeJeu->getPlayer2().getState(standby) == 1;
    bool isPlayerWin = modeJeu->getPlayerWin() != 0;
    std::stringstream textWin;

    // Lance une animation x seconde après le lancement de la partie

    switch(time) {
        case timeAnimRound:
            return displayTextAnimation(app, "Round 1 !");
        case timeAnimReady:
            return displayTextAnimation(app, "Ready ?");
        case timeAnimFight:
            modeJeu->getPlayer1().setState(standby,false);
            modeJeu->getPlayer2().setState(standby,false);
            return displayTextAnimation(app, "Fight !");
    }

    //if player wins
    if(isPlayerWin) startAnimationWin = true;
    //if one is dead and no one won yet
    else if(isPlayerDead && !isPlayerWin) startAnimationKO = true;

    //restart the clock of one animation
    if((isPlayerWin || isPlayerDead || isPlayerStandBy ) && !isClockAlreadyRestarted) startClock();

    // Lance l'animation de victoire
    if(startAnimationWin) {
            textWin << ( (modeJeu->getPlayerWin() == 1) ? (GameScreen::playerName1):(GameScreen::playerName2) ) << " Win !";
            return displayTextAnimation(app, textWin.str());
    }

    else if(startAnimationKO && timeAnimation ==2){
        modeJeu->getPlayer1().setPosition(positionP1.getX(), positionP1.getY());
        modeJeu->getPlayer2().setPosition(positionP2.getX(), positionP2.getY());
        modeJeu->getPlayer1().setSpeedX(2);
        modeJeu->getPlayer2().setSpeedX(2);
    }
    // Lance l'animation de K.O.
    else if(startAnimationKO && timeAnimation < 3) {
        modeJeu->getPlayer1().setState(standby,true);
        modeJeu->getPlayer2().setState(standby,true);
        return displayTextAnimation(app, "K.O. !");
    }
    else if(startAnimationKO && timeAnimation == 3) {
            modeJeu->getPlayer1().setState(standby,false);
            modeJeu->getPlayer2().setState(standby,false);
            modeJeu->getPlayer1().setState(dead,false);
            modeJeu->getPlayer2().setState(dead,false);
            return displayTextAnimation(app, "Fight !");
    }


    resetAnimationAndClock();
    return displayTextAnimation(app, "");
}

void GameScreen::setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app, Game* modeJeu) {

    textAnimation = displayAnimations(timer, timerAnimation, app, modeJeu);

    textAnimation.setFont(font);
    textAnimation.setCharacterSize(140);

    sf::FloatRect textRect = textAnimation.getLocalBounds();
    textAnimation.setOrigin(textRect.width/2,textRect.height/2);
}

void GameScreen::managementWin(float deltaTime, Game* modeJeu, sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app) {

    setAnimationText(timer, timerAnimation, app, modeJeu);

    if(modeJeu->getPlayerWin() == 0) {

        if(modeJeu->getPlayer1().getHealth() == 0) {

            modeJeu->incrementRoundWinP2();
            if(modeJeu->getPlayerWin() == 0) {
                modeJeu->getPlayer1().setHealth(100.f);
                modeJeu->getPlayer2().setHealth(100.f);
            }

            movePlayers(deltaTime);


        }else if(modeJeu->getPlayer2().getHealth() == 0) {
            modeJeu->incrementRoundWinP1();
            if(modeJeu->getPlayerWin() == 0) {
                modeJeu->getPlayer1().setHealth(100.f);
                modeJeu->getPlayer2().setHealth(100.f);
            }
            movePlayers(deltaTime);
        }
        else{
            movePlayers(deltaTime);
        }
    } else {
        modeJeu->win();
    }

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
