#include "HealthBarView.h"

using namespace std;

HealthBarView::HealthBarView() {
    //ctor
}

HealthBarView::HealthBarView(HealthBar *healthBar, sf::RectangleShape healthBarIn, sf::RectangleShape healthBarOut) {
    this->healthBar = *healthBar;
    this->healthBarIn = healthBarIn;
    this->healthBarOut = healthBarOut;
}

HealthBarView::~HealthBarView() {
    //dtor
}

HealthBarView::HealthBarView(const HealthBarView& other) {
    //copy ctor
}

HealthBar HealthBarView::getHealthBar() {
    return healthBar;
}

sf::RectangleShape HealthBarView::getHealthBarIn() {
    return healthBarIn;
}
sf::RectangleShape HealthBarView::getHealthBarOut() {
    return healthBarOut;
}

void HealthBarView::setPositionHealthBarIn() {
    float x=healthBar.getPosition().getX(), y=healthBar.getPosition().getY();
    healthBarIn.setPosition(x,y);
}
void HealthBarView::setPositionHealthBarOut() {
    float x=healthBar.getPosition().getX(), y=healthBar.getPosition().getY();
    healthBarOut.setPosition(x,y);
}

void HealthBarView::addColorToHealthBarIn() {
    healthBarIn.setFillColor(sf::Color::Green);
}

void HealthBarView::addColorToHealthBarOut() {
    healthBarOut.setFillColor(sf::Color::Transparent);
    healthBarOut.setOutlineThickness(2);
    healthBarOut.setOutlineColor(sf::Color::Black);
}

void HealthBarView::addSizeToHealthBarIn(){
    healthBarIn.setSize(sf::Vector2f(healthBar.getLifePoint()*3,19));
}

void HealthBarView::addSizeToHealthBarOut(){
    healthBarOut.setSize(sf::Vector2f(healthBar.getLIFE_POINT_MAX()*3,20));
}

sf::Text HealthBarView::createNamePlayer(Player player, Position posHealthBar) {

    sf::Text namePlayer;

    Position posTextBar(posHealthBar.getX(),posHealthBar.getY()+30);
//    loadFont(namePlayer, "resources/fonts/arial.ttf");
//    sf::Font font;
//    font.loadFromFile("resources/fonts/arial.ttf");
//    namePlayer.setFont(font);
    namePlayer.setString(player.getName());
    namePlayer.setCharacterSize(24);
    namePlayer.setFillColor(sf::Color::Black);
    namePlayer.setStyle(sf::Text::Bold | sf::Text::Underlined);
    namePlayer.setPosition(posTextBar.getX(),posTextBar.getY());

    return namePlayer;

}
