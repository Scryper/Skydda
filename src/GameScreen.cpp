#include "GameScreen.h"

// Load mapView (map and texture) in GameScreen
// Load all platforms in GameScreen
void GameScreen::initMap() {
    Map mapModel(mapSeed);
    map_ = MapView(mapModel, textures);

    platforms = map_.getAllCollisions();
}

// Initialize all backgrounds(size, position, texture)
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

// Load platform textures
void GameScreen::initTextures() {
    texturePlatformGround.loadFromFile("resources/images/platforms/platform_ground.png");
    texturePlatformLong.loadFromFile("resources/images/platforms/platform_long.png");
    texturePlatformSmall.loadFromFile("resources/images/platforms/platform_small.png");
    texturePlatformTiny.loadFromFile("resources/images/platforms/platform_tiny.png");
    invisibleWall.loadFromFile("resources/images/platforms/invisibleWall.jpg");
    wood.loadFromFile("resources/images/platforms/wood.png");
    houseWall.loadFromFile("resources/images/platforms/house_wall.png");
}

// Load all the textures in texture vector
void GameScreen::initVectors() {
    textures.push_back(&texturePlatformGround);
    textures.push_back(&texturePlatformLong);
    textures.push_back(&texturePlatformSmall);
    textures.push_back(&texturePlatformTiny);
    textures.push_back(&invisibleWall);
    textures.push_back(&wood);
    textures.push_back(&houseWall);
}

// Determine the state of each player and manage actions and animations
void GameScreen::movePlayers(float deltaTime) {
    playerViewP1.computeFrame(directionCollisions(playerViewP1, platforms),playerViewP2);
    playerViewP2.computeFrame(directionCollisions(playerViewP2, platforms),playerViewP1);
}

// Build text animation with style, position and appropriate text
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

// Reset the clock for next animation
void GameScreen::resetAnimationAndClock() {
    startAnimationKO = false;
    isClockAlreadyRestarted = false;
}

// Start the clock for the new animation
void GameScreen::startClock() {
    clockTimerAnimation.restart();
    isClockAlreadyRestarted = true;
    timeAnimation = 0;
}

// Return the Animation text at the right time
sf::Text GameScreen::displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app, Game* modeJeu) {
    timeAnimation = timerAnimation.asSeconds();
    int time = timer.asSeconds();
    bool isPlayerDead = modeJeu->getPlayer1().getState(dead) == 1 || modeJeu->getPlayer2().getState(dead) == 1 ;
    bool isPlayerStandBy = modeJeu->getPlayer1().getState(standby) == 1 || modeJeu->getPlayer2().getState(standby) == 1;
    bool isPlayerWin = modeJeu->getPlayerWin() != 0;
    std::stringstream textWin;

    // Launch an animation x seconds after the launch of the game
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

    if(isAlreadyWin && timeAnimation >= 3) {
            startAnimationWin = false;
            startMenu = true;
    }
    // StartAnimationWin if one of the players has won
    // and that the animation has not yet been played
    if(isPlayerWin && !isAlreadyWin) startAnimationWin = true;

    // If one is dead and no one won yet
    else if(isPlayerDead && !isPlayerWin) startAnimationKO = true;

    // Restart the clock of one of the animations
    if((isPlayerWin || isPlayerDead || isPlayerStandBy ) && !isClockAlreadyRestarted) startClock();

    // Start the victory animation for 3 seconds
    if(startAnimationWin && timeAnimation <= 3) {
            isAlreadyWin = true;
            textWin << ( (modeJeu->getPlayerWin() == 1) ? (GameScreen::playerName1):(GameScreen::playerName2) ) << " Win !";
            return displayTextAnimation(app, textWin.str());
    }

    // Start the KO animation for 2 seconds
    else if(startAnimationKO && timeAnimation ==2) {
        modeJeu->getPlayer1().setPosition(positionP1);
        modeJeu->getPlayer2().setPosition(positionP2);
        modeJeu->getPlayer1().setSpeedX(2);
        modeJeu->getPlayer2().setSpeedX(2);
        modeJeu->getPlayer1().setState(dead,false);
        modeJeu->getPlayer2().setState(dead,false);
        if(!playerViewP1.isLooksRigth()){
           playerViewP1.flipSprite();
           playerViewP1.setLooksRigth(true);
        }
        if(playerViewP2.isLooksRigth()){
            playerViewP2.flipSprite();
            playerViewP2.setLooksRigth(false);
        }
        // Start the Round animation for 2 seconds
        if(!isAlreadyWin && instanceof<GameRound>(modeJeu)){
            Game* tmp = (Game*)modeJeu;
            int total = tmp->getRoundWinP1();
            total += tmp->getRoundWinP2() + 1;
            return displayTextAnimation(app, "Round " + std::to_string(total));
        }
        return displayTextAnimation(app, "K.O. !");
    }
    // Start the KO animation for 2 seconds
    else if(startAnimationKO && timeAnimation < 3) {
        modeJeu->getPlayer1().setState(standby,true);
        modeJeu->getPlayer2().setState(standby,true);

        return displayTextAnimation(app, "K.O. !");
    }
    // Start the Fight animation for 3 seconds
    else if(!isAlreadyWin && startAnimationKO && timeAnimation == 3) {
            modeJeu->getPlayer1().setState(standby,false);
            modeJeu->getPlayer2().setState(standby,false);
            return displayTextAnimation(app, "Fight !");
    }


    resetAnimationAndClock();
    return displayTextAnimation(app, "");
}

// Build textAnimation thanks to displayAnimations method
void GameScreen::setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app, Game* modeJeu) {

    textAnimation = displayAnimations(timer, timerAnimation, app, modeJeu);

    textAnimation.setFont(font);
    textAnimation.setCharacterSize(140);

    sf::FloatRect textRect = textAnimation.getLocalBounds();
    textAnimation.setOrigin(textRect.width/2,textRect.height/2);
}

// Manage game victory and round victory, Reset life on next round
void GameScreen::managementWin(float deltaTime, Game* modeJeu, sf::Time timer, sf::Time timerAnimation, sf::RenderWindow *app) {

    setAnimationText(timer, timerAnimation, app, modeJeu);
    // If none of the players won
    if(modeJeu->getPlayerWin() == 0) {
        // If player 1 is dead
        if(modeJeu->getPlayer1().getHealth() == 0) {
            modeJeu->incrementRoundWinP2();
            // If none of the players won
            if(modeJeu->getPlayerWin() == 0) {
                modeJeu->getPlayer1().setHealth(100.f);
                modeJeu->getPlayer2().setHealth(100.f);
            }
            movePlayers(deltaTime);
        }
        // If player 2 is dead
        else if(modeJeu->getPlayer2().getHealth() == 0) {
            modeJeu->incrementRoundWinP1();
            // If none of the players won
            if(modeJeu->getPlayerWin() == 0) {
                modeJeu->getPlayer1().setHealth(100.f);
                modeJeu->getPlayer2().setHealth(100.f);
            }
            movePlayers(deltaTime);
        }
        else{
            movePlayers(deltaTime);
        }
    }
    // If one of the players has won
    else {
        if(startWinningSound) {
            SoundManager* soundManager = SoundManager::getInstance();
            soundManager->playVictorySound();
            startWinningSound = false;
        }
    }

}

// Initializes the life bar and the name player
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

// Determines if one object is an instance of another
template<typename Base, typename T>
inline bool GameScreen::instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}
