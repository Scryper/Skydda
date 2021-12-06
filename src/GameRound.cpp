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

GameRound& GameRound::operator=(const GameRound& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    Game::operator=(rhs);
    return *this;
}

int GameRound::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) return 1;
    else if(roundWinP2 == MAX_ROUND) return 2;
    else return 0;
}
