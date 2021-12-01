#include "GameTimer.h"

GameTimer::GameTimer()
:Game() {

}

GameTimer::GameTimer(Player& player1, Player& player2)
:Game(player1, player2) {

}

GameTimer::~GameTimer()
{
    //dtor
}

GameTimer::GameTimer(const GameTimer& other)
{
    //copy ctor
}

int GameTimer::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) return 1;
    else if(roundWinP2 == MAX_ROUND) return 2;
    else return 0;
}
