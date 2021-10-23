#include "Movement.h"

Movement::Movement() {
    CoupleFloat tmpSpeed;
    speed = tmpSpeed;
    CoupleFloat tmpAcceleration;
    acceleration = tmpAcceleration;
}

Movement::Movement(CoupleFloat speed, CoupleFloat acceleration) {
    this->speed = speed;
    this->acceleration = acceleration;
}

Movement::~Movement() {

}

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

Position Movement::updatePosition(Position position, CoupleFloat coupleFloat){
    position.setX(position.getX() + coupleFloat.getX());
    position.setY(position.getY() + coupleFloat.getY());
    return position;
}
