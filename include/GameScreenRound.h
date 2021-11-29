#ifndef GAMESCREENROUND_H
#define GAMESCREENROUND_H
#include "GameScreen.h"
#include <string>

class GameScreenRound : public GameScreen {
    private:

    public:
        GameScreenRound();
        virtual ~GameScreenRound();
        GameScreenRound(const GameScreenRound& other);
        GameScreenRound& operator=(const GameScreenRound& other);

        virtual sf::Text displayAnimations(sf::Time timer, sf::RenderWindow &app);

        sf::Text displayTextAnimation(sf::RenderWindow &app, std::string text);

};

#endif // GAMESCREENROUND_H