#include "GameRound.h"

GameRound::GameRound():Game() {}

GameRound::GameRound(Player& player1, Player& player2)
:Game(player1, player2) {}

GameRound::~GameRound() {}

GameRound::GameRound(const GameRound& other) {}

GameRound& GameRound::operator=(const GameRound& rhs) {
    if (this == &rhs) return *this;
    Game::operator=(rhs);
    return *this;
}

// Returns the number of the winning player
// Or 0 if no one has won
int GameRound::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) return 1;
    else if(roundWinP2 == MAX_ROUND) return 2;
    else return 0;
}
