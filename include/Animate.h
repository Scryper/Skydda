#ifndef ANIMATE_H
#define ANIMATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class Animate
{
    public:
        Animate();
        virtual ~Animate();
        sf::Sprite draw();
        void update(float deltaTime);

    protected:

    private:
        sf::Texture *texture;
        float currentFrame{};
        sf::Clock* animationClock;
        vector<sf::Texture*> frames;

};

#endif // ANIMATE_H
