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

int GameTimer::getPlayerWin(int time) {

    if(time>=25) {
        if(roundWinP1>roundWinP2) {
            return 1;
        } else if(roundWinP2>roundWinP1) {
            return 2;
        } else {
            return 0;
        }
    }
    return 0;

}

void GameTimer::incrementRoundWinP1(int time) {
    if(getPlayerWin(time) == 0 && roundWinP1 < MAX_ROUND) {
        roundWinP1++;
    }
}
void GameTimer::incrementRoundWinP2(int time) {
    if(getPlayerWin(time) == 0 && roundWinP2 < MAX_ROUND) {
        roundWinP2++;
    }
}
