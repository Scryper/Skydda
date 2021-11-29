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

        virtual void displayAnimations(sf::Time timer, sf::RenderWindow &app);

        void displayTextAnimation(sf::RenderWindow &app, std::string text);

};

#endif // GAMESCREENROUND_H
