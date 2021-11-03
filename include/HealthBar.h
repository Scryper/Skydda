#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "Position.h"

class HealthBar
{
    private:
        float lifePoint;
        float LIFE_POINT_MAX=100.f;
        Position position;

    public:
        HealthBar();
        HealthBar(float lifePoint, float posX, float posY);
        virtual ~HealthBar();
        HealthBar(const HealthBar& other);

        float getLifePoint();
        float getLIFE_POINT_MAX();
        Position getPosition();

};

#endif // HEALTHBAR_H
