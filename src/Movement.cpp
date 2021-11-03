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
    //vertical acceleration is constant
    CoupleFloat couple(acceleration.getX(), 5.f);
    this->acceleration = couple;
}

void Movement::stopX(){
    this->speed.setX(0);
}

void Movement::stopY(){
    this->speed.setY(0);
}

Position Movement::updatePosition(Position position, CoupleFloat direction, std::vector<int> collisions) {
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

    ///////////// DIRECTION X /////////////

    // if X direction = 0 -> slow down
    if(directionX == 0){
        // if speed goes towards right and (speed - acceleration) > 0
        if(speedX > 0 && speedX - accelerationX >= 0) {
            speed.setX(speedX - accelerationX);
        }
        // if speed goes towards right and (speed - acceleration) < 0
        else if(speedX > 0 && speedX - accelerationX <= 0) {
            speed.setX(0);
        }

        // if speed goes towards left and (speed - acceleration) < 0
        if(speedX < 0 && speedX - accelerationX < 0) {
            speed.setX(speedX + accelerationX);
        }
        // if speed goes towards left and (speed - acceleration) > 0
        else if(speedX < 0 && speedX - accelerationX > 0) {
            speed.setX(0);
        }
    }
    // x direction != 0
    else {
        // we verify we go toxards left with negative max speed or more
        if(left && speedX<=-maxSpeedX) {
            speed.setX(-maxSpeedX); // we can't have speed > maxSpeed
        }
        // we verify we go towards right with positive maxSpeed or more
        else if(right && speedX >= maxSpeedX){
            speed.setX(maxSpeedX); // we can't have speed > maxSpeed
        }
        // if the player is not moving at max speed, we increment the speed in the correct direction
        else if(left) {
            speed.setX(speedX - accelerationX);
        }
        else if(right) {
            speed.setX(speedX + accelerationX);
        }
    }

    ///////////// DIRECTION Y /////////////

    // if y direction = 0 -> gravity gives vertical speed
    if(directionY == 0){
        // if the player moves at max speed
        if(speedY >= maxSpeedY){
            speed.setY(maxSpeedY);
        }
        else{
            // if not, we increment vertical speed
            speed.setY(speedY + accelerationY);
        }
    }
    // y direction != 0
    else {
        // if y speed = 0, give speed towards top
        // !! verify if there is a collision underneath
        if(speedY == 0 /*&& collisions != -1*/){
            speed.setY(-20.f);
        }
        // if speed != 0 we can't jump again -> normal acceleration
        // if the player moves with max speed
        else if(speedY>=maxSpeedY){
            speed.setY(maxSpeedY);
        }
        // if speed < max speed, we increment vertical speed towards bottom
        else {
            speed.setY(speedY + accelerationY);
        }
    }
    /*
    //on boucle sur la liste des int des collisions
    switch(collisions){
        case 1 :
            if(speed.getY() < 0)
                speed.setY(0);
            break;
        case 2 :
            if(speed.getY() > 0)
                speed.setY(0);
            break;

        case 3 :
            if(speed.getX() < 0)
                speed.setX(0);
            break;
        case 4 :
            if(speed.getX() > 0)
                speed.setX(0);
            break;
        default :
            break;
    }
*/
    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());
    std::cout<< "speed x = " << speed.getX()<<std::endl;

    return position;
}
