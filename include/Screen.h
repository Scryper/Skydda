#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "SpriteInitializer.h"
#include "TextInitializer.h"

class Screen {
    private:
        int middleScreenX;
        int middleScreenY;
        Position center;

    public:
        virtual int run(sf::RenderWindow &app) = 0;

        sf::Vector2f getMousePosition(sf::RenderWindow *app) const;
        Position getScreenCenter(sf::RenderWindow *app);
};

#endif // SCREEN_H
