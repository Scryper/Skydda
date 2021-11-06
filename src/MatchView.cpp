#include "MatchView.h"

MatchView::MatchView(){
    Game game;
    this->game = game;
}

MatchView::MatchView(Game& game){
    this->game = game;
}

MatchView::~MatchView()
{
    //dtor
}

MatchView::MatchView(const MatchView& other)
{
    //copy ctor
}

Game& MatchView::getGame() {
    return game;
}


std::vector<sf::CircleShape> MatchView::getRoundCirclesP1() {
    return roundCirclesP1;
}

std::vector<sf::CircleShape> MatchView::getRoundCirclesP2() {
    return roundCirclesP2;
}
