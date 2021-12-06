#include "HealthBarView.h"

HealthBarView::HealthBarView() { }

HealthBarView::HealthBarView(HealthBar *healthBar, sf::RectangleShape healthBarIn, sf::RectangleShape healthBarOut) {
    this->healthBar = *healthBar;
    this->healthBarIn = healthBarIn;
    this->healthBarOut = healthBarOut;
}

HealthBarView::~HealthBarView() { }

HealthBarView::HealthBarView(const HealthBarView& other) { }

HealthBarView& HealthBarView::operator=(const HealthBarView& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->healthBar = rhs.healthBar;
    this->healthBarIn = rhs.healthBarIn;
    this->healthBarOut = rhs.healthBarOut;
    return *this;
}

///Getter
HealthBar HealthBarView::getHealthBar() {
    return healthBar;
}

sf::RectangleShape HealthBarView::getHealthBarIn() {
    return healthBarIn;
}
sf::RectangleShape HealthBarView::getHealthBarOut() {
    return healthBarOut;
}

///Setter
void HealthBarView::setPositionHealthBarIn() {
    float x = healthBar.getPosition().getX();
    float y = healthBar.getPosition().getY();
    healthBarIn.setPosition(x, y);
}
void HealthBarView::setPositionHealthBarOut() {
    float x = healthBar.getPosition().getX();
    float y = healthBar.getPosition().getY();
    healthBarOut.setPosition(x, y);
}

//set the color of the remaining life
void HealthBarView::actualiseColorHealthBarIn() {
    healthBarIn.setFillColor(sf::Color::Green);
}

//set the color of the life lost
void HealthBarView::actualiseColorHealthBarOut() {
    healthBarOut.setFillColor(sf::Color::Red);
    healthBarOut.setOutlineThickness(2);
    healthBarOut.setOutlineColor(sf::Color::Black);
}

//update the size of the bar representing the health left
void HealthBarView::actualiseSizeHealthBarIn(float hpPlayer){
    healthBarIn.setSize(sf::Vector2f(hpPlayer * 3, 20));
}

//update the size of the bar representing the health lost
void HealthBarView::actualiseSizeHealthBarOut(){
    healthBarOut.setSize(sf::Vector2f(healthBar.getLIFE_POINT_MAX() * 3, 20));
}

//create the name of the player under the healthBar
sf::Text HealthBarView::createNamePlayer(Player player, Position posHealthBar) {
    sf::Text namePlayer = TextInitializer::createText(player.getName(), posHealthBar);

    namePlayer.setFillColor(sf::Color::Black);
    namePlayer.setStyle(sf::Text::Bold | sf::Text::Underlined);

    return namePlayer;
}
