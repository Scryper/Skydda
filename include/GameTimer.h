#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "Game.h"
#include "GlobalVariables.h"

class GameTimer: public Game {
    protected:
        int MAX_ROUND = 1000;
        float COUNTDOWN = 60.;

    public:
        GameTimer();
        GameTimer(Player& player1, Player& player2);
        virtual ~GameTimer();
        GameTimer(const GameTimer& other);
        GameTimer& operator=(const GameTimer& other);


        virtual int getPlayerWin();

        void decrementCountDown();

        float getCountDown();
        void initHealthBars();

};

#endif // GAMETIMER_H
