#include "Movement.h"

Movement::Movement() {
    CoupleFloat defaultSpeed;
    this->speed = defaultSpeed;

    CoupleFloat defaultAcceleration;
    this->acceleration = defaultAcceleration;

    CoupleFloat defaultMaxSpeed;
    this->maxSpeed = defaultMaxSpeed;

    this->jumpHeight = 25.f;
}

Movement::Movement(CoupleFloat speed, CoupleFloat acceleration, CoupleFloat maxSpeed, float jumpHeight) {
    this->speed = speed;
    this->acceleration = acceleration;
    this->maxSpeed = maxSpeed;
    this->jumpHeight = jumpHeight;
}

Movement::~Movement() { }

Movement::Movement(const Movement& other) {
    this->speed = other.speed;
    this->acceleration = other.acceleration;
    this->maxSpeed = other.maxSpeed;
    this->jumpHeight = other.jumpHeight;
}

Movement& Movement::operator=(const Movement& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->speed = rhs.speed;
    this->acceleration = rhs.acceleration;
    this->maxSpeed = rhs.maxSpeed;
    this->jumpHeight = rhs.jumpHeight;
    return *this;
}

///Getter
CoupleFloat Movement::getSpeed()const {
    return speed;
}
CoupleFloat Movement::getAcceleration()const {
    return acceleration;
}

///Setter
void Movement::setSpeed(CoupleFloat speed) {
    this->speed = speed;
}
void Movement::setAcceleration(CoupleFloat acceleration){
    //vertical acceleration is constant
    CoupleFloat couple(acceleration.getX(), 5.f);
    this->acceleration = couple;
}

//put the speed in x to 0
void Movement::stopX(){
    this->speed.setX(0);
}

//put the speed in y to 0
void Movement::stopY(){
    this->speed.setY(0);
}

//apply recoil to the movement
void Movement::recoil(int value){
    speed.setX(value);
}

//update the position of an object based on the speed
Position Movement::updatePosition(Position position, CoupleFloat direction, std::vector<CollisionVector> collisions) {
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

    bool zeroY = false;

    CollisionVector coll;


    ///////////// DIRECTION X /////////////

    // if X direction = 0 -> slow down
    if(directionX == 0) {
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
        if(left && speedX <= -maxSpeedX) {
            speed.setX(-maxSpeedX); // we can't have speed > maxSpeed
        }
        // we verify we go towards right with positive maxSpeed or more
        else if(right && speedX >= maxSpeedX) {
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
        if(speedY >= maxSpeedY) {
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
        if(speedY == 0 && zeroY == true){
            speed.setY(-jumpHeight);
        }
        // if speed != 0 we can't jump again -> normal acceleration
        // if the player moves with max speed
        else if(speedY >= maxSpeedY){
            speed.setY(maxSpeedY);
        }
        // if speed < max speed, we increment vertical speed towards bottom
        else {
            speed.setY(speedY + accelerationY);
        }
    }

    //check the collisions and the direction of the collisions
    for(auto& i : collisions){
        for(auto& j : i){
            switch(j.first){
                case bottom :
                    if(speed.getY() < 0){
                        coll.push_back(j);
                    }
                    break;

                case top :
                    if(directionY != 0 && speedY == 0){
                        speed.setY(-jumpHeight);
                    }
                    else if(speed.getY() > 0){
                        coll.push_back(j);
                    }
                    break;

                case rigthCol :
                    if(speed.getX() < 0){
                        coll.push_back(j);
                    }
                    break;

                case leftCol :
                    if(speed.getX() > 0){
                        coll.push_back(j);
                    }
                    break;

                default :
                    break;
            }
        }


        for(auto i : coll){
            if(i.first == bottom || i.first == top){
                speed.setY(0);
                position.setY(i.second);
            }
            if(i.first == leftCol || i.first == rigthCol){
                speed.setX(0);
                position.setX(i.second);
            }
        }
    }


    //update the position
    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());
    return position;
}
