#include "GameTimer.h"

GameTimer::GameTimer()
:Game() {

}

GameTimer::GameTimer(Player& player1, Player& player2)
:Game(player1, player2) {

}

GameTimer::~GameTimer() {
    //dtor
}

GameTimer::GameTimer(const GameTimer& other) {
    //copy ctor
}

GameTimer& GameTimer::operator=(const GameTimer& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    Game::operator=(rhs);
    return *this;
}

int GameTimer::getPlayerWin() {

//    std::cout << "roundWinP1 : " << roundWinP1 << std::endl;
//    std::cout << "roundWinP2 : " << roundWinP2 << std::endl;

    if(COUNTDOWN<=0) {
        if(player1->getPoints()>player2->getPoints()) {
            return 1;
        } else if(player2->getPoints()>player1->getPoints()) {
            return 2;
        } else {
            return 0;
        }
    }
    return 0;

}

void GameTimer::decrementCountDown() {
    if(COUNTDOWN>0) {
        COUNTDOWN -= 1./GlobalVariables::FPS;
    }
}

float GameTimer::getCountDown() {
    return COUNTDOWN;
}
