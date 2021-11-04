#include "Match.h"
#include <iostream>

using namespace std;

Match::Match(Player& player1, Player& player2) {
    this->player1 = &player1;
    this->player2 = &player2;
    //this->player1.setAlive(false);
    roundWinP1 = 0;
    roundWinP2 = 0;
}

Match::~Match() {
    //dtor
}

Match::Match(const Match& other) {
    //copy ctor
}

void Match::incrementRoundWinP1() {
    if(getPlayerWin()==0 && roundWinP1 < MAX_ROUND){
        roundWinP1++;
    }
}

void Match::incrementRoundWinP2() {

    if(getPlayerWin()==0 && roundWinP2 < MAX_ROUND){
        roundWinP2++;
    }

}

Player& Match::getPlayer1() {
    return *player1;
}
Player& Match::getPlayer2() {
    return *player2;
}

void Match::win() {
    player1->setAlive(false);
    player2->setAlive(false);
}

int Match::getRoundWinP1() {
    return roundWinP1;
}

int Match::getRoundWinP2() {
    return roundWinP2;
}

int Match::getPlayerWin() {
    if(roundWinP1 == MAX_ROUND) {
        return 1;
    } else if(roundWinP2 == MAX_ROUND) {
        return 2;
    } else {
        return 0;
    }
}
