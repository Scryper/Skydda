#include "Game.h"

#include <iostream>

using namespace std;

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

Game::~Game() {
    //dtor
}

Game::Game(const Game& other) {
    //copy ctor
}

void Game::incrementRoundWinP1() {
    if(getPlayerWin()==0 && roundWinP1 < MAX_ROUND){
        roundWinP1++;
    }
}

void Game::incrementRoundWinP2() {

    if(getPlayerWin()==0 && roundWinP2 < MAX_ROUND){
        roundWinP2++;
    }

}

Player& Game::getPlayer1() {
    return *player1;
}
Player& Game::getPlayer2() {
    return *player2;
}

void Game::win() {
    player1->setAlive(false);
    player2->setAlive(false);
}

int Game::getRoundWinP1() {
    return roundWinP1;
}

int Game::getRoundWinP2() {
    return roundWinP2;
}

int Game::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) {
        return 1;
    } else if(roundWinP2 == MAX_ROUND) {
        return 2;
    } else {
        return 0;
    }
}

