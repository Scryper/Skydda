#ifndef GAMEROUND_H
#define GAMEROUND_H
#include "Game.h"

class GameRound : public Game {
    protected:
        int MAX_ROUND = 3;

    public:
        GameRound();
        GameRound(Player& player1, Player& player2);
        virtual ~GameRound();
        GameRound(const GameRound& other);

        int getPlayerWin();
        //virtual int getPlayerWin(int timer);

        void incrementRoundWinP1();
        void incrementRoundWinP2();
};

#endif // GAMEROUND_H
