#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "SpriteInitializer.h"
#include "TextInitializer.h"

class Screen {
    public:
        virtual int run(sf::RenderWindow &app) = 0;

        sf::Vector2f getMousePosition(sf::RenderWindow *app) const;
};

#endif // SCREEN_H
