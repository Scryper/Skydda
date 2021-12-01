#ifndef GAMESCREENROUND_H
#define GAMESCREENROUND_H
#include "GameScreen.h"
#include "GameRound.h"

#include <string>

class GameScreenRound : public GameScreen {
    protected:
        GameRound gameRound;

    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
        GameScreenRound();
        virtual ~GameScreenRound();
        GameScreenRound(const GameScreenRound& other);

        virtual sf::Text displayAnimations(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app);
        virtual void setAnimationText(sf::Time timer, sf::Time timerAnimation, sf::RenderWindow &app);

        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();

        void createRoundCircles();
        void actualiseRoundCircles();
        void clearRoundCircles();

        void initHealthBars();

        GameRound& getGameRound();

};

#endif // GAMESCREENROUND_H
