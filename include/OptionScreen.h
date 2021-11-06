#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H

#include "Screen.h"

class OptionScreen : public Screen {
    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // OPTIONSCREEN_H
