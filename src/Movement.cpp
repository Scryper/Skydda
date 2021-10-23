#include "Movement.h"

Movement::Movement() {
    CoupleFloat tmpSpeed;
    speed = tmpSpeed;

    CoupleFloat tmpAcceleration;
    acceleration = tmpAcceleration;
}

Movement::Movement(CoupleFloat speed, CoupleFloat acceleration, CoupleFloat maxSpeed) {
    this->speed = speed;
    this->acceleration = acceleration;
    this->maxSpeed = maxSpeed;
}

Movement::~Movement() { }

Movement::Movement(const Movement& other) {
    speed = other.speed;
    acceleration = other.acceleration;
}

CoupleFloat Movement::getSpeed()const {
    return speed;
}
CoupleFloat Movement::getAcceleration()const {
    return acceleration;
}

void Movement::setSpeed(CoupleFloat speed) {
    this->speed = speed;
}
void Movement::setAcceleration(CoupleFloat acceleration){
    this->acceleration = acceleration;
}

Position Movement::updatePosition(Position position, CoupleFloat direction) {
    float speedX = speed.getX();
    float directionX = direction.getX();
    float maxSpeedX = maxSpeed.getX();
    //float accelerationX = acceleration.getX();
    float productX = speedX * directionX;
    bool left = directionX < 0;
    std::cout << left << std::endl;

    float speedY = speed.getY();
    float directionY = direction.getY();
    float maxSpeedY = maxSpeed.getY();
    //float accelerationY = acceleration.getY();
    float productY = speedY * directionY;
    bool up = directionY < 0;

    if(productX >= maxSpeedX) {
        if(left) {
            speed.setX(-maxSpeedX);
        }
        else {
            speed.setX(maxSpeedX);
        }
    }
    else {
        if(left) {
            speed.setX(--speedX);// - accelerationX);
        }
        else {
            speed.setX(++speedX);// + accelerationX);
        }
    }

    if(productY >= maxSpeedY) {
        if(up) {
            speed.setY(-maxSpeedY);
        }
        else {
            speed.setY(maxSpeedY);
        }
    }
    else {
        if(up) {
            speed.setY(--speedY);// - accelerationY);
        }
        else {
            speed.setY(++speedY);// + accelerationY);
        }
    }

    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());
    return position;
}
