#ifndef CHOOSECHARACTERSCREEN_H
#define CHOOSECHARACTERSCREEN_H

#include "Screen.h"

class ChooseCharacterScreen : public Screen {
    public:
        std::string strFirstPlayerName;
        std::string strSecondPlayerName;
        int map_; // Because map is keyword

        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // CHOOSECHARACTERSCREEN_H
