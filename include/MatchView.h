#ifndef MATCHVIEW_H
#define MATCHVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Match.h"

class MatchView {
    private:
        Match match;
        std::vector<sf::CircleShape> roundCirclesP1;
        std::vector<sf::CircleShape> roundCirclesP2;

    public:
        MatchView();
        MatchView(Match& match);
        virtual ~MatchView();
        MatchView(const MatchView& other);

        void createRoundCircles(Position posP1, Position posP2);
        void actualiseRoundCircles();
        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();

        Match& getMatch();
};

#endif // MATCHVIEW_H
