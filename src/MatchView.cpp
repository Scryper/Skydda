#include "MatchView.h"

MatchView::MatchView()
{
    //ctor
}

MatchView::~MatchView()
{
    //dtor
}

MatchView::MatchView(const MatchView& other)
{
    //copy ctor
}

void MatchView::createRoundCircles() {
    sf::CircleShape roundCircle1(10);
    roundCircle1.setFillColor(sf::Color(100, 250, 50));
    sf::CircleShape roundCircle2(10);
    roundCircle2.setFillColor(sf::Color(100, 250, 50));
    sf::CircleShape roundCircle3(10);
    roundCircle3.setFillColor(sf::Color(100, 250, 50));

    roundCircle1.setPosition(200.f,200.f);
    roundCircle2.setPosition(300.f,200.f);
    roundCircle3.setPosition(400.f,200.f);

    roundCircles.push_back(roundCircle1);
    roundCircles.push_back(roundCircle2);
    roundCircles.push_back(roundCircle3);
}

std::vector<sf::CircleShape> MatchView::getRoundCircles() {
    return roundCircles;
}
