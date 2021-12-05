#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "StatePlayer.h"



class Animation {
    private:
        PlayerStateClockArray stateClocks;
        AnimStateTours tours;
        PlayerStateEnum lastState;

    public:
        Animation();
        virtual ~Animation();
        Animation(const Animation& other);
        Animation& operator=(const Animation& other);

        void initClocks();
        void initClock(PlayerStateEnum state);
        void destroyClocks();
        void initTours();
        void initTour(PlayerStateEnum state);
        void destroyTours();

        PlayerStateClockArray* getStateClock();
        void resetTour(PlayerStateEnum state);

        sf::IntRect animate(int row, int frame, float x, float y);
        void startAnimation(PlayerSprite* sprite, PlayerStateEnum newState, bool isPlayedOneTime);

};

#endif // ANIMATION_H
