#ifndef GAMESCREENTIMER_H
#define GAMESCREENTIMER_H
#include "GameScreen.h"
#include "GameTimer.h"

class GameScreenTimer : public GameScreen {
    protected:
        GameTimer gameTimer;


    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
        GameScreenTimer();
        virtual ~GameScreenTimer();
        GameScreenTimer(const GameScreenTimer& other);
        GameScreenTimer& operator=(const GameScreenTimer& other);

        virtual sf::Text displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app);

        virtual void setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app);


};

#endif // GAMESCREENTIMER_H
