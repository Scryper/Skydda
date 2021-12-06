#ifndef GAMESCREENROUND_H
#define GAMESCREENROUND_H
#include "GameScreen.h"
#include "GameRound.h"

#include <string>

class GameScreenRound : public GameScreen {
    private:
        const static inline std::string TEXT_PLAY_AGAIN = "Play again";
        const static inline std::string TEXT_SELECT_CHARACTERS = "Select characters";
        const static inline std::string TEXT_MAIN_MENU = "Main menu";

        sf::Clock clock;
        sf::Clock clockTimer;

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

        void drawAll(sf::RenderWindow *app);

        void setMenuText(sf::RenderWindow *app);
        void initPlayers();
};

#endif // GAMESCREENROUND_H
