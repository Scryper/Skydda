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

Player& Game::getPlayer1() {
    return *player1;
}
Player& Game::getPlayer2() {
    return *player2;
}

void Game::win() {
    SoundManager* soundManager = SoundManager::getInstance();
    soundManager->playVictorySound();
    player1->setState(dead,true);
    player2->setState(dead,true);
}

int Game::getRoundWinP1() {
    return roundWinP1;
}

int Game::getRoundWinP2() {
    return roundWinP2;
}

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
