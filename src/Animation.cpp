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

    //destroy all clocks
    destroyClocks();

    //copy all clocks
    PlayerStateClockArray tmp;
    this->stateClocks = tmp;
    for(auto i : other.stateClocks){
        PlayerStateClock* clockTemp = new PlayerStateClock;
        clockTemp->first = i->first;
        clockTemp -> second = new sf::Clock;
        this->stateClocks.push_back(clockTemp);
    }

    //destroy all tours
    destroyTours();

    //copy all tours
    AnimStateTours animTmp;
    this->tours = animTmp;
    for(auto i : other.tours){
        animStateTour* anim = new animStateTour;
        *(anim) = *(i);
        this->tours.push_back(anim);
    }

    return *this;
}

//init all tours based on state and in wich turn they are
void Animation::initTours(){
    for(auto i : constPlayerStates){
        initTour(i.state);
    }
}

//init one turn (need pointers and new)
void Animation::initTour(PlayerStateEnum s){
    animStateTour* temp(0);
    temp = new animStateTour;

    animStateTour temp2 = {s,0};
    *temp=temp2;
    tours.push_back(temp);
}

//destroy all tours
void Animation::destroyTours(){
    for(auto i : tours){
        delete i;
    }
    tours.clear();
}

//init all clocks
void Animation::initClocks(){
    for(auto i : constPlayerStates){
        initClock(i.state);
    }
}

//init one particular clock with pointers
void Animation::initClock(PlayerStateEnum s){
    PlayerStateClock *temp(0);
    temp = new PlayerStateClock;

    sf::Clock *tempClock(0);
    tempClock = new sf::Clock;

    PlayerStateClock temp2 = {s,tempClock};
    *temp = temp2;
    stateClocks.push_back(temp);
}

//destroy each particular instance (pointer of pointer)
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

//reinitialize the numero of the frame of the anim
void Animation::resetTour(PlayerStateEnum state){
    tours[state]->tour=0;
}

//return the sprite need for this specific frame
sf::IntRect Animation::animate(int row, int frame, float x, float y)
{
    return sf::IntRect(frame * x, row * y, x, y);
}

//
void Animation::startAnimation(PlayerSprite* sprite, PlayerStateEnum state, bool isPlayedOneTime)
{

    //get the row and the maximum of frame of the animation of this state
    int row = constAnimState[state].row;
    int maxFrame = constAnimState[state].maxFrame;

    float x = sprite->getOrigin().x * 2;
    float y = sprite->getOrigin().y * 2;

    //find the clock of the state
    sf::Clock clock;
    for(auto clockTMP : stateClocks){
        if(clockTMP->first==state){
            clock = *(clockTMP->second);
        }
    }

    //if it is a new animation
    if(lastState!=state){
        tours[state]->tour = 0;
    }

    //get the current frame
    int tour = tours[state]->tour;

    //if not played only once or if the max frame is not reached yet
    if(!isPlayedOneTime || tour<maxFrame){
        //get time in millisedons
        int time = clock.getElapsedTime().asMilliseconds();
        int animDuration = 0;
        if (time % 3 == 0){

            //get if the animation is a timed one
            bool isTimed = 0;
            for(auto i : constPlayerStates){
                if(state==i.state&& i.isTimed==1){
                    isTimed=1;
                    animDuration = i.animationDuration;
                }
            }

            //if the animation is timed
            if(isTimed){
                //if the timer limit is reached, we don't update the frame
                if(time<=animDuration&& tour<maxFrame){
                    tours[state]->tour++;
                }
            }
            //if it is not an timed animation
            else{
                if (tour == maxFrame) tours[state]->tour = 0;
                else tours[state]->tour++;
            }
        }
        //setting the rigth texture to the sprite
        sprite->setTextureRect(sf::IntRect(tours[state]->tour*x, row * y, x, y));
    }

    //to remember wich anim we just played
    lastState = state;
}
