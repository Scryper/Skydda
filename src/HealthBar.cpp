#include "HealthBar.h"
using namespace std;

HealthBar::HealthBar()
{
    //ctor
}

HealthBar::HealthBar(float lifePoint, float posX, float posY)
{
    this->lifePoint = lifePoint;
    Position position(posX, posY);
    this->position = position;
}

HealthBar::HealthBar(float lifePoint, Position position){
    this->lifePoint = lifePoint;
    this->position = position;
}

HealthBar::~HealthBar()
{
    //dtor
}

HealthBar::HealthBar(const HealthBar& other)
{
    //copy ctor
}

float HealthBar::getLifePoint(){
    return lifePoint;
}

float HealthBar::getLIFE_POINT_MAX() {
    return LIFE_POINT_MAX;
}

Position HealthBar::getPosition() {
    return position;
}
