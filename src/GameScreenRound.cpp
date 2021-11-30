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

GameScreenRound& GameScreenRound::operator=(const GameScreenRound& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

sf::Text GameScreenRound::displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app) {

    timeAnimation = timerAnimation.asSeconds();
    int time = timer.asSeconds();
    bool isPlayerDead = game.getPlayer1().getHealth() == 0 || game.getPlayer2().getHealth() == 0;
    bool isPlayerWin = game.getPlayerWin() != 0;
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
            textWin << "Player" << ((game.getPlayerWin() == 1)?"1":"2") << " Win !";
            return displayTextAnimation(app, textWin.str());
    }
    // Lance l'animation de K.O.
    else if(startAnimationKO && timeAnimation < 3) return displayTextAnimation(app, "K.O. !");

    resetAnimationAndClock();
    return displayTextAnimation(app, "");
}

void GameScreenRound::resetAnimationAndClock() {
    startAnimationKO = false;
    isClockAlreadyRestarted = false;
}

void GameScreenRound::startClock() {
    clockTimerAnimation.restart();
    isClockAlreadyRestarted = true;
    timeAnimation = 0;
}

sf::Text GameScreenRound::displayTextAnimation(sf::RenderWindow &app, std::string textStr) {
    const int SCRWIDTH = app.getSize().x;
    const int SCRHEIGHT = app.getSize().y -200;

    Position position(SCRWIDTH/2.0f, SCRHEIGHT/2.0f);
    sf::Text textAnimation = TextInitializer::createText(textStr, position);

    textAnimation.setFillColor(sf::Color::Red);
    textAnimation.setOutlineColor(sf::Color::Black);
    textAnimation.setOutlineThickness(4);

    return textAnimation;
}
