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

    switch(time) {
        case 3:
            return displayTextAnimation(app, "Round 1 !");
        case 5:
            return displayTextAnimation(app, "Ready ?");
        case 7:
            return displayTextAnimation(app, "Fight !");
    }

    if(game.getPlayer1().getHealth() == 0 || game.getPlayer2().getHealth() == 0) {
        if(game.getPlayerWin() == 0) startAnimationKO = true;
    }

    if(game.getPlayerWin() == 1 || game.getPlayerWin() == 2) {
        startAnimationWin = true;
    }

    if(startAnimationWin) {
        if(!isClockAlreadyRestarted) {
            clockTimerAnimation.restart();
            isClockAlreadyRestarted = true;
            timeAnimation = 0;
        }
        if(timeAnimation < 50) {
            return (game.getPlayerWin() == 1)
            ? displayTextAnimation(app, "Player 1 Win !")
            : displayTextAnimation(app, "Player 2 Win !");
        } else {
            startAnimationWin = false;
            isClockAlreadyRestarted = false;
            return displayTextAnimation(app, "");
        }
    } else if(startAnimationKO) {
        if(!isClockAlreadyRestarted) {
            clockTimerAnimation.restart();
            isClockAlreadyRestarted = true;
            timeAnimation = 0;
        }
        if(timeAnimation < 3) {
            return displayTextAnimation(app, "K.O. !");
        } else {
            startAnimationKO = false;
            isClockAlreadyRestarted = false;
            return displayTextAnimation(app, "");
        }
    } else {
        return displayTextAnimation(app, "");
    }

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
