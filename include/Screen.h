#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "SpriteInitializer.h"

class Screen {
    public:
        virtual int run(sf::RenderWindow &app) = 0;
};

#endif // SCREEN_H
