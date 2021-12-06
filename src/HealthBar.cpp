#include "HealthBar.h"
using namespace std;

HealthBar::HealthBar() { }

HealthBar::HealthBar(float lifePoint, float posX, float posY) {
    this->lifePoint = lifePoint;
    Position position(posX, posY);
    this->position = position;
}

HealthBar::HealthBar(float lifePoint, Position position){
    this->lifePoint = lifePoint;
    this->position = position;
}

HealthBar::~HealthBar() { }

HealthBar::HealthBar(const HealthBar& other) { }

HealthBar& HealthBar::operator=(const HealthBar& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->lifePoint = rhs.lifePoint;
    this->position = rhs.position;
    return *this;
}

///Getter
float HealthBar::getLifePoint(){
    return lifePoint;
}

float HealthBar::getLIFE_POINT_MAX() {
    return LIFE_POINT_MAX;
}

Position HealthBar::getPosition() {
    return position;
}
