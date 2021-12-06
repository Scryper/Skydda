#include "Game.h"

Game::Game() {
    this->roundWinP1 = 0;
    this->roundWinP2 = 0;
}

Game::Game(Player& player1, Player& player2) {
    this->player1 = &player1;
    this->player2 = &player2;
    this->roundWinP1 = 0;
    this->roundWinP2 = 0;
}

Game::~Game() { }
Game::Game(const Game& other) { }

Game& Game::operator=(const Game& rhs) {
    if (this == &rhs) return *this;
    this->player1 = rhs.player1;
    this->player2 = rhs.player2;
    this->roundWinP1 = rhs.roundWinP1;
    this->roundWinP2 = rhs.roundWinP2;
    return *this;
}

Player& Game::getPlayer1() {
    return *player1;
}
Player& Game::getPlayer2() {
    return *player2;
}

// Return the number of round won by the player
int Game::getRoundWinP1() {
    return roundWinP1;
}
int Game::getRoundWinP2() {
    return roundWinP2;
}

// Increment by one the number of turns won by the player
void Game::incrementRoundWinP1() {
    if(getPlayerWin() == 0) {
        roundWinP1++;
    }
}
void Game::incrementRoundWinP2() {
    if(getPlayerWin() == 0) {
        roundWinP2++;
    }
}
