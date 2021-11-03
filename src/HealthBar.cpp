#include "HealthBar.h"

HealthBar::HealthBar()
{
    //ctor
}

HealthBar::HealthBar(float lifePoint, float posX, float posY)
{
    this->lifePoint = lifePoint;
    Position position(posX, posY);
}

HealthBar::~HealthBar()
{
    //dtor
}

HealthBar::HealthBar(const HealthBar& other)
{
    //copy ctor
}
