#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "StatePlayer.h"



class Animation {
    private:
        PlayerStateClockArray stateClocks;
        int state;
        int frame;
        int tour;
        int maxFrame;
        sf::Clock clock;

    public:
        Animation();
        virtual ~Animation();
        Animation(const Animation& other);

        void initClocks();

        sf::IntRect animate(int state, int frame, float x, float y);
        bool startAnimation(PlayerSprite* sprite, int newState);

};

#endif // ANIMATION_H
