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
    return 0;
}

int GameTimer::getPlayerWin(int time) {

    if(time==25) {
        if(roundWinP1>roundWinP2) {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 0;
    }

}
