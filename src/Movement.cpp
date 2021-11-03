
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
    CoupleFloat cf(acceleration.getX(),5.f);
    this->acceleration = cf;
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


    ///////////////////////////////////////
    ///////////// DIRECTION X /////////////
    ///////////////////////////////////////

    //si la direction X est nulle -> ralentir
    if(directionX==0){

         //si la vitesse est vers la droite et que (la vitesse - l'accélération) est positive
         if(speedX > 0 && speedX - accelerationX >= 0) {
            speed.setX(speedX - accelerationX);
        }
        else{
            //si la vitesse est vers la droite et que la (vitesse - l'accélération) est négative
            if(speedX > 0 && speedX - accelerationX <= 0) {
                speed.setX(0);
            }
        }

        //si la vitesse est vers la gauche et que (la vitesse - l'accélération) est négative
        if(speedX < 0 && speedX - accelerationX < 0) {
            speed.setX(speedX + accelerationX);
        }
        else{
            //si la vitesse est vers la gauche et que la (vitesse - l'accélération) est positive
            if(speedX < 0 && speedX - accelerationX > 0) {
                speed.setX(0);
            }
        }

    }
    //la direction X n'est pas nulle
    else{
        //on vérifie qu'on va a gauche en étant a la vitesse max ou plus (en négatif)
        if(left && speedX<=-maxSpeedX) {
            speed.setX(-maxSpeedX);
        }
        //on vérifie qu'on va a droite en étant a la vitesse max ou plus (en positif
        else if(right&&speedX>=maxSpeedX){
            speed.setX(maxSpeedX);
        }
        //sinon si la vitesse max n'est pas atteinte, on incrémente la vitesse dans la direction donnée
        else {
            if(left) {
                speed.setX(speedX - accelerationX);
            }
            else if(right) {
                speed.setX(speedX + accelerationX);
            }
        }
    }

    ///////////////////////////////////////
    ///////////// DIRECTION Y /////////////
    ///////////////////////////////////////


    //si la direction Y est nulle -> gravité qui donne une vitesse verticale
    if(directionY==0){
        //si la vitesse est maximale
        if(speedY>=maxSpeedY){
            speed.setY(maxSpeedY);
        }
        else{
            //si la vitesse n'est pas maximale on accélère vers le bas
            speed.setY(speedY + accelerationY);
        }
    }

    else{
        //la direction n'est pas nulle

        //si la vitesseY = 0 , on lui donne une vitesse vers le haut de XXXX
        //attention de bien vérifier qu'il y a une collision en dessous
        if(speedY==0){
            speed.setY(-10.f);
        }
        else{
            //si la vitesse est != 0 on ne peut pas re-sauter!!!!  il y a donc juste l'accélération normale
            //si la vitesse est maximale
            if(speedY>=maxSpeedY){
                speed.setY(maxSpeedY);
            }
            else{
                //si la vitesse n'est pas maximale on accélère vers le bas
                speed.setY(speedY + accelerationY);
            }
        }
    }


    position.setX(position.getX() + speed.getX());
    position.setY(position.getY() + speed.getY());
    std::cout<< "speed x = " << speed.getX()<<std::endl;

    return position;
}
