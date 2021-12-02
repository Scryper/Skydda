#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "StatePlayer.h"



class Animation {
    private:
        PlayerStateClockArray stateClocks;
        int frame;
        int tour;
        int maxFrame;

    public:
        Animation();
        virtual ~Animation();
        Animation(const Animation& other);

        void initClocks();
        void initClock(PlayerStateEnum state);
        PlayerStateClockArray* getStateClock();

        sf::IntRect animate(int row, int frame, float x, float y);
        void startAnimation(PlayerSprite* sprite, PlayerStateEnum newState, bool boucle);

};

#endif // ANIMATION_H
