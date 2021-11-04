#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"

class MenuScreen : public Screen {
    public:
        virtual int run(sf::RenderWindow &app);
};

#endif // MENUSCREEN_H
