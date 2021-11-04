#ifndef MATCH_H
#define MATCH_H
#include "Player.h"

class Match
{
    private:
        Player* player1;
        Player* player2;
        int roundWinP1;
        int roundWinP2;
        int MAX_ROUND=3;

    public:
        Match(Player& player1, Player& player2);
        virtual ~Match();
        Match(const Match& other);

        void incrementRoundWinP1();
        void incrementRoundWinP2();

        int getRoundWinP1();
        int getRoundWinP2();

        Player& getPlayer1();
        Player& getPlayer2();

        int getPlayerWin();

        void win();

};

#endif // MATCH_H
