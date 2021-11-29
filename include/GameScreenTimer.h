#ifndef GAMESCREENTIMER_H
#define GAMESCREENTIMER_H
#include "GameScreen.h"

class GameScreenTimer : public GameScreen {
    private:

    public:
        GameScreenTimer();
        virtual ~GameScreenTimer();
        GameScreenTimer(const GameScreenTimer& other);
        GameScreenTimer& operator=(const GameScreenTimer& other);

        virtual sf::Text displayAnimations(sf::Time timer);

};

#endif // GAMESCREENTIMER_H
