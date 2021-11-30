#ifndef GAMESCREENROUND_H
#define GAMESCREENROUND_H
#include "GameScreen.h"
#include <string>

class GameScreenRound : public GameScreen {
    protected:


    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
        GameScreenRound();
        virtual ~GameScreenRound();
        GameScreenRound(const GameScreenRound& other);
        GameScreenRound& operator=(const GameScreenRound& other);

        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();

        void createRoundCircles();
        void actualiseRoundCircles();
        void clearRoundCircles();

        void initHealthBars();

};

#endif // GAMESCREENROUND_H
