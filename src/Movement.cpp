#include "Movement.h"

Movement::Movement() {
    CoupleFloat defaultSpeed;
    this->speed = defaultSpeed;

    CoupleFloat defaultAcceleration;
    this->acceleration = defaultAcceleration;

    CoupleFloat defaultMaxSpeed;
    this->maxSpeed = defaultMaxSpeed;
}

Movement::Movement(CoupleFloat speed, CoupleFloat acceleration, CoupleFloat maxSpeed) {
    this->speed = speed;
    this->acceleration = acceleration;
    this->maxSpeed = maxSpeed;
}

Movement::~Movement() { }

Movement::Movement(const Movement& other) {
    this->speed = other.speed;
    this->acceleration = other.acceleration;
    this->maxSpeed = other.maxSpeed;
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
    // get the info about X movement
    float speedX = speed.getX();
    float directionX = direction.getX();
    float maxSpeedX = maxSpeed.getX();
    float accelerationX = acceleration.getX();
    bool left = directionX < 0;
    bool right = directionX > 0;

    // get the info about Y movement
    float speedY = speed.getY();
    float directionY = direction.getY();
    float maxSpeedY = maxSpeed.getY();
    float accelerationY = acceleration.getY();
    bool up = directionY < 0;
    bool down = directionY > 0;

    float productX = speedX * accelerationX;
    float productY = speedY * accelerationY;

    if(directionX == 0 && directionY == 0) {
        if(speedX > 0 && speedX - accelerationX > 0) {
            speed.setX(speedX - accelerationX);
        }
        if(speedX < 0 && speedX - accelerationX < 0) {
            speed.setX(speedX + accelerationX);
        }
        if(speedY > 0 && speedY - accelerationY > 0) {
            speed.setY(speedY - accelerationY);
        }
        if(speedY < 0 && speedY - accelerationY < 0) {
            speed.setY(speedY + accelerationY);
        }
    } else {
        if(abs(speedX) >= maxSpeedX) {
            if(left) {
                speed.setX(-maxSpeedX);
            }
            else if(right) {
                speed.setX(maxSpeedX);
            }
        }
        else {
            if(left) {
                speed.setX(speedX - accelerationX);
            }
            else if(right) {
                speed.setX(speedX + accelerationX);
            }
        }

        if(abs(speedY) >= maxSpeedY) {
            if(up) {
                speed.setY(-maxSpeedY);
            }
            else if(down) {
                speed.setY(maxSpeedY);
            }
        }
        else {
            if(up) {
                speed.setY(speedY - accelerationY);
            }
            else if(down)  {
                speed.setY(speedY + accelerationY);
            }
        }
    }

    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());

    return position;
}
