#include "Animate.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

Animate::Animate()
{

    animationClock = new sf::Clock;

    for (const auto& path : {
        "resources/images/character/walk/mario_1_1.png",
        "resources/images/character/walk/mario_1_2.png",
        "resources/images/character/walk/mario_1_3.png",
        "resources/images/character/walk/mario_1_4.png",
    }) {
        auto frame = new sf::Texture();
        frame->loadFromFile(path);
        frames.push_back(frame);
    }
    texture = frames[0];
}

Animate::~Animate()
{
    for (const auto& ptr : frames) {
        delete ptr;
    }
    delete animationClock;
}
sf::Sprite Animate::draw()
{
    sf::Sprite playerSprite(*texture);
    return playerSprite;
}

void Animate::update(float deltaTime)
{
    currentFrame += deltaTime * 4;
    if (currentFrame > frames.size()) {
        currentFrame -= frames.size();
    }
    texture = frames[(int)currentFrame];

}
