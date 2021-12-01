#include "GameRound.h"

GameRound::GameRound():Game() {

}

GameRound::GameRound(Player& player1, Player& player2)
:Game(player1, player2) {

}

GameRound::~GameRound() {
    //dtor
}

GameRound::GameRound(const GameRound& other) {
    //copy ctor
}

int GameRound::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) return 1;
    else if(roundWinP2 == MAX_ROUND) return 2;
    else return 0;
}

void GameRound::incrementRoundWinP1() {
    if(getPlayerWin() == 0 && roundWinP1 < MAX_ROUND) {
        roundWinP1++;
    }
}
void GameRound::incrementRoundWinP2() {
    if(getPlayerWin() == 0 && roundWinP2 < MAX_ROUND) {
        roundWinP2++;
    }
}