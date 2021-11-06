#ifndef MATCHVIEW_H
#define MATCHVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

class MatchView {
    private:
        Game game;
        std::vector<sf::CircleShape> roundCirclesP1;
        std::vector<sf::CircleShape> roundCirclesP2;

    public:
        MatchView();
        MatchView(Game& game);
        virtual ~MatchView();
        MatchView(const MatchView& other);

        void createRoundCircles(Position posP1, Position posP2);
        void actualiseRoundCircles();
        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();

        Game& getGame();
};

#endif // MATCHVIEW_H
