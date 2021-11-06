#ifndef PREMATCHSCREEN_H
#define PREMATCHSCREEN_H

#include "Screen.h"

class PrematchScreen : public Screen {
    public:
        std::string strFirstPlayerName;
        std::string strSecondPlayerName;
        int map_; // Because map is keyword

        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // PREMATCHSCREEN_H
