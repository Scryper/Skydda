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

GameScreenTimer& GameScreenTimer::operator=(const GameScreenTimer& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

sf::Text GameScreenTimer::displayAnimations(sf::Time timer) {
    std::cout << "GameScreenTimer" << std::endl;
    Position position(0, 0);
    sf::Text tmpText = TextInitializer::createText("", position);
    return tmpText;
}
