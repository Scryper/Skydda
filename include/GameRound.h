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
        GameRound& operator=(const GameRound& other);

        virtual int getPlayerWin();
};

#endif // GAMEROUND_H
