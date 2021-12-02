#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "Game.h"
#include "GlobalVariables.h"

class GameTimer: public Game {
    private:
        int MAX_ROUND = 1000;
        float COUNTDOWN = 25.;


    public:
        GameTimer();
        GameTimer(Player& player1, Player& player2);
        virtual ~GameTimer();
        GameTimer(const GameTimer& other);

        //virtual int getPlayerWin();
        int getPlayerWin(int timer);

        void incrementRoundWinP1(int timer);
        void incrementRoundWinP2(int timer);

        void decrementCountDown();

        float getCountDown();

};

#endif // GAMETIMER_H
