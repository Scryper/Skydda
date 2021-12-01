#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
    protected:
        Player* player1;
        Player* player2;
        int roundWinP1;
        int roundWinP2;
        int MAX_ROUND;

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

        virtual int getPlayerWin()=0;
        virtual int getPlayerWin(int time)=0;

        void win();

};

#endif // GAME_H
