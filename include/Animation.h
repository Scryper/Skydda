#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"



class Animation {
    private:
        int state;
        int frame;
        int tour;
        int maxFrame;
        sf::Clock clock;

    public:
        Animation();
        virtual ~Animation();
        Animation(const Animation& other);

        sf::IntRect animate(int state, int frame, float x, float y);
        bool startAnimation(PlayerSprite* sprite, int newState);

};

#endif // ANIMATION_H
