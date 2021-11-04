#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"

class MenuScreen : public Screen {
    public:
        MenuScreen();
        virtual ~MenuScreen();

        virtual int run(sf::RenderWindow &app);
};

#endif // MENUSCREEN_H
