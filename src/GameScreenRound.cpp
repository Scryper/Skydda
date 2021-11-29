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

sf::Text GameScreenRound::displayAnimations(sf::Time timer, sf::RenderWindow &app) {

    int time = timer.asSeconds();
    std::cout << timer.asSeconds() << std::endl;
    switch(time) {
        case 3:
            return displayTextAnimation(app, "Round 1 !");
        case 5:
            return displayTextAnimation(app, "Ready ?");
        case 7:
            return displayTextAnimation(app, "Fight !");
        case 9:
            return displayTextAnimation(app, "K.O. !");
        case 11:
            return displayTextAnimation(app, "Player 1 Win !");
        default:
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
