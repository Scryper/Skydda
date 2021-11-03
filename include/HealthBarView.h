#ifndef HEALTHBARVIEW_H
#define HEALTHBARVIEW_H
#include <SFML/Graphics.hpp>
#include "HealthBar.h"
#include "Player.h"


class HealthBarView {
    private:
        HealthBar healthBar;
        sf::RectangleShape healthBarIn;
        sf::RectangleShape healthBarOut;

    public:
        HealthBarView();
        HealthBarView(HealthBar *healthBar, sf::RectangleShape healthBarIn, sf::RectangleShape healthBarOut);
        virtual ~HealthBarView();
        HealthBarView(const HealthBarView& other);

        HealthBar getHealthBar();

        sf::RectangleShape getHealthBarIn();
        sf::RectangleShape getHealthBarOut();


        void setPositionHealthBarIn();
        void setPositionHealthBarOut();

        void addColorToHealthBarIn();
        void addColorToHealthBarOut();

        void addSizeToHealthBarIn();
        void addSizeToHealthBarOut();

        sf::Text createNamePlayer(Player player, Position posHealthBar);


};

#endif // HEALTHBARVIEW_H
