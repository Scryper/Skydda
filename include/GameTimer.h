#ifndef GAMETIMER_H
#define GAMETIMER_H
#include "Game.h"

class GameTimer: public Game {
    private:
        int MAX_ROUND = 1000;

    public:
        GameTimer();
        GameTimer(Player& player1, Player& player2);
        virtual ~GameTimer();
        GameTimer(const GameTimer& other);

        //virtual int getPlayerWin();
        int getPlayerWin(int timer);

        void incrementRoundWinP1(int timer);
        void incrementRoundWinP2(int timer);

};

#endif // GAMETIMER_H