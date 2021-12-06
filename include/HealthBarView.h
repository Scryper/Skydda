#ifndef HEALTHBARVIEW_H
#define HEALTHBARVIEW_H

#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Player.h"
#include "TextInitializer.h"

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
        HealthBarView& operator=(const HealthBarView& other);


        HealthBar getHealthBar();

        sf::RectangleShape getHealthBarIn();
        sf::RectangleShape getHealthBarOut();

        void setLifePoint(float lifePoint);

        void setPositionHealthBarIn();
        void setPositionHealthBarOut();

        void actualiseColorHealthBarIn();
        void actualiseColorHealthBarOut();

        void actualiseSizeHealthBarIn(float hpPlayer);
        void actualiseSizeHealthBarOut();

        sf::Text createNamePlayer(Player player, Position posHealthBar);
};

#endif // HEALTHBARVIEW_H
