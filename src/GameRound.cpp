#include "GameRound.h"

GameRound::GameRound()
:Game() {

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
//    std::cout << "roundWinP1 : " << roundWinP1 << std::endl;
//    std::cout << "roundWinP2 : " << roundWinP2 << std::endl;

    if(roundWinP1 == MAX_ROUND) return 1;
    else if(roundWinP2 == MAX_ROUND) return 2;
    else return 0;
}
