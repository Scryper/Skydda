#ifndef GAMESCREENTIMER_H
#define GAMESCREENTIMER_H
#include "GameScreen.h"
#include "GameTimer.h"

class GameScreenTimer : public GameScreen {
    protected:

    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
        GameScreenTimer();
        virtual ~GameScreenTimer();
        GameScreenTimer(const GameScreenTimer& other);
        GameScreenTimer& operator=(const GameScreenTimer& other);

        virtual void drawAll(sf::RenderWindow *app, sf::Text *timeTxt);
        void setTextTime(sf::Text *timeTxt);
};

#endif // GAMESCREENTIMER_H
