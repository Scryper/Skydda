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

void GameScreenRound::displayAnimations(sf::Time timer, sf::RenderWindow &app) {

    int time = timer.asSeconds();
    switch(time) {
        case 3:
            displayTextAnimation(app, "Round 1 !");
            break;
        case 5:
            displayTextAnimation(app, "Ready ?");
            break;
        case 7:
            displayTextAnimation(app, "Fight !");
            break;
        case 9:
            displayTextAnimation(app, "K.O. !");
            break;
        case 11:
            displayTextAnimation(app, "Player 1 Win !");
            break;
    }
}

void GameScreenRound::displayTextAnimation(sf::RenderWindow &app, std::string text) {
    Position position(app.getView().getCenter().x -400,app.getView().getCenter().y -200);
    sf::Text textAnimation = TextInitializer::createText(text, position);
    sf::Font font;
    font.loadFromFile("resources/fonts/glitch.otf");
    textAnimation.setCharacterSize(150);
    textAnimation.setFont(font);
    app.draw(textAnimation);
    app.display();
}
