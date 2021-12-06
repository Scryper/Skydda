#include "Animation.h"
#include <iostream>

Animation::Animation() {
    initClocks();
    initTours();
}


Animation::Animation(const Animation& other) {
    initClocks();
    initTours();
}

Animation::~Animation() {
    destroyClocks();
    destroyTours();
}

Animation& Animation::operator=(const Animation& other){
    if (this == &other) return *this;

    this->lastState = other.lastState;

    destroyClocks();

    PlayerStateClockArray tmp;
    this->stateClocks = tmp;
    for(auto i : other.stateClocks){
        PlayerStateClock* clockTemp = new PlayerStateClock;
        clockTemp->first = i->first;
        clockTemp -> second = new sf::Clock;
        this->stateClocks.push_back(clockTemp);
    }

    destroyTours();
    AnimStateTours animTmp;
    this->tours = animTmp;
    for(auto i : other.tours){
        animStateTour* anim = new animStateTour;
        *(anim) = *(i);
        this->tours.push_back(anim);
    }

    return *this;
}

void Animation::initTours(){
    for(auto i : constPlayerStates){
        initTour(i.state);
    }
}

void Animation::initTour(PlayerStateEnum s){
    animStateTour* temp(0);
    temp = new animStateTour;

    animStateTour temp2 = {s,0};
    *temp=temp2;
    tours.push_back(temp);
}

void Animation::destroyTours(){
    for(auto i : tours){
        delete i;
    }
    tours.clear();
}

void Animation::initClocks(){
    for(auto i : constPlayerStates){
        initClock(i.state);
    }
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

void Animation::destroyClocks(){
    for(auto i : stateClocks){
        delete i->second;
        delete i;
    }
    stateClocks.clear();
}

PlayerStateClockArray* Animation::getStateClock(){
    return &stateClocks;
}

void Animation::resetTour(PlayerStateEnum state){
    tours[state]->tour=0;
}

sf::IntRect Animation::animate(int row, int frame, float x, float y)
{
    return sf::IntRect(frame * x, row * y, x, y);
}

void Animation::startAnimation(PlayerSprite* sprite, PlayerStateEnum state, bool isPlayedOneTime)
{

    //std::cout<<"animation état : " << state<<std::endl;
    int row = constAnimState[state].row;
    int maxFrame = constAnimState[state].maxFrame;

    float x = sprite->getOrigin().x * 2;
    float y = sprite->getOrigin().y * 2;

    sf::Clock clock;
    //find the clock
    for(auto clockTMP : stateClocks){
        if(clockTMP->first==state){
            clock = *(clockTMP->second);
        }
    }

    if(lastState!=state){
        tours[state]->tour = 0;
    }

    int tour = tours[state]->tour;
    //s'il n'est pas joué qu'une seule fois ou qu'on a atteint la frame limite
    if(!isPlayedOneTime || tour<maxFrame){
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
                if(time<=animDuration&& tour<maxFrame){
                    tours[state]->tour++;
                }
            }
            //si ce n'est pas un state timed
            else{
                if (tour == maxFrame) tours[state]->tour = 0;
                else tours[state]->tour++;
            }
        }
        sprite->setTextureRect(sf::IntRect(tours[state]->tour*x, row * y, x, y));
    }

    lastState = state;
}
