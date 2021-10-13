#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Position.h"
#include "CoupleFloat.h"

class Movement {
    private:
        CoupleFloat speed;
        CoupleFloat acceleration;

    public:
        Movement();
        Movement(CoupleFloat speed, CoupleFloat acceleration);
        Movement(const Movement& other);
        virtual ~Movement();

        CoupleFloat getSpeed()const;
        CoupleFloat getAcceleration()const;

        void setSpeed(CoupleFloat speed);
        void setAcceleration(CoupleFloat acceleration);

        void updatePosition(Position position, float deltaTime);

};

#endif // MOVEMENT_H
