#include "MatchView.h"

MatchView::MatchView(){
    Match match;
    this->match = match;
}

MatchView::MatchView(Match& match){
    this->match = match;
}

MatchView::~MatchView()
{
    //dtor
}

MatchView::MatchView(const MatchView& other)
{
    //copy ctor
}

Match& MatchView::getMatch() {
    return match;
}

void MatchView::createRoundCircles(Position posP1, Position posP2) {

    sf::CircleShape roundCircle(10);
    roundCircle.setFillColor(sf::Color::Transparent);
    roundCircle.setOutlineThickness(3);
    roundCircle.setOutlineColor(sf::Color::Black);

    // P1
    roundCircle.setPosition(posP1.getX(),posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    roundCircle.setPosition(posP1.getX()+50,posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    roundCircle.setPosition(posP1.getX()+100,posP1.getY());
    roundCirclesP1.push_back(roundCircle);

    // P2
    roundCircle.setPosition(posP2.getX()+200,posP2.getY());
    roundCirclesP2.push_back(roundCircle);

    roundCircle.setPosition(posP2.getX()+250,posP2.getY());
    roundCirclesP2.push_back(roundCircle);

    roundCircle.setPosition(posP2.getX()+300,posP2.getY());
    roundCirclesP2.push_back(roundCircle);

}

void MatchView::actualiseRoundCircles() {

    switch(match.getRoundWinP1()) {
        case 1:
            roundCirclesP1[0].setFillColor(sf::Color::White);
            break;
        case 2:
            roundCirclesP1[1].setFillColor(sf::Color::White);
            break;
        case 3:
            roundCirclesP1[2].setFillColor(sf::Color::White);
            break;
    }
    switch(match.getRoundWinP2()) {
        case 1:
            roundCirclesP2[0].setFillColor(sf::Color::White);
            break;
        case 2:
            roundCirclesP2[1].setFillColor(sf::Color::White);
            break;
        case 3:
            roundCirclesP2[2].setFillColor(sf::Color::White);
            break;
    }
}

std::vector<sf::CircleShape> MatchView::getRoundCirclesP1() {
    return roundCirclesP1;
}

std::vector<sf::CircleShape> MatchView::getRoundCirclesP2() {
    return roundCirclesP2;
}
