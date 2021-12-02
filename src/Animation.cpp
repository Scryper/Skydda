#include "Animation.h"
#include <iostream>

Animation::Animation() {
    initClocks();
}


Animation::Animation(const Animation& other) {
}

Animation::~Animation() {

}

void Animation::initClocks(){

}

sf::IntRect Animation::animate(int state, int frame, float x, float y)
{
    return sf::IntRect(frame * x, state * y, x, y);
}

bool Animation::startAnimation(PlayerSprite* sprite, int newState)
{

    switch(newState)
    {
    case 5:
        this->maxFrame = 6;
        break;
    default:
        this->maxFrame = 12;
        break;
    }

    float x = sprite->getOrigin().x * 2;
    float y = sprite->getOrigin().y * 2;
    this->maxFrame -= 1;
    if (this->clock.getElapsedTime().asMilliseconds() % 3 == 0){

        if (this->tour == this->maxFrame || (this->state != newState && (this->state != 1 && this->state != 3))){
            this->tour = 0;
        }
        else{
            this->tour += 1;
        }

        if((this->state != 3 && this->state != 1) || (tour == 0 && (state == 1 || state == 3)))
        {
        this->state = newState;
        }

        sprite->setTextureRect(sf::IntRect(this->tour * x, (this->state-1) * y, x, y));

    }

    return true;

}


/*
{
    float x = this->sprite.getOrigin().x * 2;
    float y = this->sprite.getOrigin().y * 2;

    this->maxFrame -= 1;
    if (this->clock.getElapsedTime().asMilliseconds() % 3 == 0){

        if (this->tour == this->maxFrame || (this->lastState != this->state && (this->lastState != 1 && this->lastState != 3))){
            this->tour = 0;
        }
        else{
            this->tour += 1;
        }

        if((this->lastState != 3 && this->lastState != 1) || (tour == 0 && (lastState == 1 || lastState == 3)))
        {
        this->lastState = this->state;
        }

        this->sprite.setTextureRect(sf::IntRect(this->tour * x, (this->lastState-1) * y, x, y));

    }
}

*/
