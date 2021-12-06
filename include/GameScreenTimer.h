#ifndef GAMESCREENTIMER_H
#define GAMESCREENTIMER_H
#include "GameScreen.h"
#include "GameTimer.h"

class GameScreenTimer : public GameScreen {
    protected:
        sf::Text timeTxt;
        Position positionTimeTxt;

        sf::Text RoundWinTxtP1;
        Position positionRoundWinTxtP1;
        sf::Text RoundWinTxtP2;
        Position positionRoundWinTxtP2;


    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
        GameScreenTimer();
        virtual ~GameScreenTimer();
        GameScreenTimer(const GameScreenTimer& other);
        GameScreenTimer& operator=(const GameScreenTimer& other);

        void drawAll(sf::RenderWindow *app);
        void setTextTime(int SCRWIDTH);
        void setTextRoundWin();

        void setMenuText(sf::RenderWindow *app);
        void initPlayers();
};

#endif // GAMESCREENTIMER_H
