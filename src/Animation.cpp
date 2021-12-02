#include "Animation.h"
#include <iostream>

Animation::Animation() {
    initClocks();
}


Animation::Animation(const Animation& other) {
    initClocks();
}

Animation::~Animation() {
    stateClocks.clear();
}

void Animation::initClocks(){
    initClock(dead);
    initClock(standby);
    initClock(defending);
    initClock(receiveDamage);
    initClock(attacking);
    initClock(jumping);
    initClock(movingLeft);
    initClock(movingRight);
    initClock(momentum);
    initClock(idle);
    tour = 0 ;
}

void Animation::initClock(PlayerStateEnum s){
    PlayerStateClock *temp(0);
    temp = new PlayerStateClock;

    sf::Clock *tempClock(0);
    tempClock = new sf::Clock;

    PlayerStateClock temp2 = {s,tempClock};
    *temp = temp2;
    stateClocks.push_back(temp);
}

PlayerStateClockArray* Animation::getStateClock(){
    return &stateClocks;
}

sf::IntRect Animation::animate(int row, int frame, float x, float y)
{
    return sf::IntRect(frame * x, row * y, x, y);
}

void Animation::startAnimation(PlayerSprite* sprite, PlayerStateEnum state, bool boucle)
{
    int row;
    maxFrame = 12-1;
    switch(state){
    case dead:
        row = 1;
        break;
    case standby:
        row = 3;
        break;
    case defending:
        row = 2;
        maxFrame=12-1;
        break;
    case receiveDamage:
        row = 2;
        break;
    case attacking:
        row = 0;
        break;
    case jumping :
        maxFrame=6-1;
        row = 4;
        break;
    case movingLeft:
        row = 5;
        break;
    case movingRight:
        row = 5;
        break;
    case momentum :
        row = 3;
        break;
    case idle:
        row = 3;
        break;
    }

    float x = sprite->getOrigin().x * 2;
    float y = sprite->getOrigin().y * 2;

    sf::Clock clock;
    //find the clock
    for(auto clockTMP : stateClocks){
        if(clockTMP->first==state){
            clock = *(clockTMP->second);
        }
    }

    int time = clock.getElapsedTime().asMilliseconds();
    int animDuration = 0;
    if (time % 3 == 0){
        //si c'est un state timed
        bool isTimed = 0;
        for(auto i : constPlayerStates){
            if(state==i.state&& i.isTimed==1){
                isTimed=1;
                animDuration = i.animationDuration;
            }
        }

        if(isTimed){
            //si le timer a été dépassé, on n'update plus l'image
            std::cout<<time<<" " <<animDuration<<std::endl;
            if(time<=animDuration&& tour<maxFrame){
                tour++;
            }
        }
        //si ce n'est pas un state timed
        else{
            if (tour == maxFrame) tour = 0;
            else tour++;
        }
    }
        sprite->setTextureRect(sf::IntRect(tour*x, row * y, x, y));
}
