#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Position.h"
#include "CoupleFloat.h"

#include <stdlib.h>
#include <iostream>

class Movement {
    private:
        CoupleFloat speed;
        CoupleFloat acceleration;
        CoupleFloat maxSpeed;

    public:
        Movement();
        Movement(CoupleFloat speed, CoupleFloat acceleration, CoupleFloat maxSpeed);
        Movement(const Movement& other);
        virtual ~Movement();

        CoupleFloat getSpeed() const;
        CoupleFloat getAcceleration() const;

        void setSpeed(CoupleFloat speed);
        void setAcceleration(CoupleFloat acceleration);

        Position updatePosition(Position position, CoupleFloat coupleFloat);
};

#endif // MOVEMENT_H
