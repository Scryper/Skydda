#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
    private:
        Player* player1;
        Player* player2;
        int roundWinP1;
        int roundWinP2;
        int MAX_ROUND = 3; //const static
    public:
        Game();
        Game(Player& player1, Player& player2);
        virtual ~Game();
        Game(const Game& other);

        void incrementRoundWinP1();
        void incrementRoundWinP2();

        int getRoundWinP1();
        int getRoundWinP2();

        Player& getPlayer1();
        Player& getPlayer2();

        int getPlayerWin();

        void win();
};

#endif // GAME_H
