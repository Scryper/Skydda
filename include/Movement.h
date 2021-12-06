#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Position.h"
#include "CoupleFloat.h"

#include <stdlib.h>
#include <vector>
#include "EnumCollision.h"
#include <iostream> // to delete when debug ok

/*This class is used to recalculate the player's position when he is moving.*/
class Movement {
    private:
        CoupleFloat speed;
        CoupleFloat acceleration;
        CoupleFloat maxSpeed;
        float jumpHeight;

    public:
        Movement();
        Movement(CoupleFloat speed, CoupleFloat acceleration, CoupleFloat maxSpeed, float jumpHeight);
        Movement(const Movement& other);
        virtual ~Movement();
        Movement& operator=(const Movement& other);

        ///Getter
        CoupleFloat getSpeed() const;
        CoupleFloat getAcceleration() const;

        ///Setter
        void setSpeed(CoupleFloat speed);
        void setAcceleration(CoupleFloat acceleration);

        //to set the speed in x to 0
        void stopX();
        //to set the speed in y to 0
        void stopY();
        //apply recoil to the movement
        void recoil(int value);

        //calculate the new position
        Position updatePosition(Position position, CoupleFloat coupleFloat, std::vector<CollisionVector> collisions);
};

#endif // MOVEMENT_H
