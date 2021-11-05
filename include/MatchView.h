#ifndef MATCHVIEW_H
#define MATCHVIEW_H
#include <SFML/Graphics.hpp>
#include <vector>

class MatchView {
    private:
        std::vector<sf::CircleShape> roundCircles;

    public:
        MatchView();
        virtual ~MatchView();
        MatchView(const MatchView& other);

        void createRoundCircles();
        std::vector<sf::CircleShape> getRoundCircles();
};

#endif // MATCHVIEW_H
