#include "Movement.h"

Movement::Movement() {
    CoupleFloat tmpSpeed;
    speed = tmpSpeed;

    CoupleFloat tmpAcceleration;
    acceleration = tmpAcceleration;

    CoupleFloat tmpMaxSpeed;
    maxSpeed = tmpMaxSpeed;
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
    maxSpeed = other.maxSpeed;
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
    float accelerationX = acceleration.getX();
    float productX = speedX * accelerationX;
    bool left = directionX < 0;
    bool right = directionX > 0;

    float speedY = speed.getY();
    float directionY = direction.getY();
    float maxSpeedY = maxSpeed.getY();
    float accelerationY = acceleration.getY();
    float productY = speedY * accelerationY;
    bool up = directionY < 0;
    bool down = directionY > 0;

    if(productX >= maxSpeedX) {
        if(left) {
            speed.setX(-maxSpeedX);
        }
        else if(right) {
            speed.setX(maxSpeedX);
        }
    }
    else {
        if(left) {
            speed.setX(speedX - accelerationX);// - accelerationX);
        }
        else if(right) {
            speed.setX(speedX + accelerationX);// + accelerationX);
        }
    }

    if(productY >= maxSpeedY) {
        if(up) {
            speed.setY(-maxSpeedY);
        }
        else if(down) {
            speed.setY(maxSpeedY);
        }
    }
    else {
        if(up) {
            speed.setY(speedY - accelerationY);// - accelerationY);
        }
        else if(down)  {
            speed.setY(speedY + accelerationY);// + accelerationY);
        }
    }

    //std::cout << "speedX : " << speed.getX() << std::endl;
    //std::cout << "speedY : " << speed.getY() << std::endl;

    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());
    return position;
}
