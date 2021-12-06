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


        ///Getter
        HealthBar getHealthBar();

        sf::RectangleShape getHealthBarIn();
        sf::RectangleShape getHealthBarOut();

        ///Setter
        void setLifePoint(float lifePoint);

        //set the color of the life left
        void setPositionHealthBarIn();
        //set the color of the life lost
        void setPositionHealthBarOut();

        //update the size of the bar representing the health left
        void actualiseColorHealthBarIn();
        //update the size of the bar representing the health lost
        void actualiseColorHealthBarOut();

        void actualiseSizeHealthBarIn(float hpPlayer);
        void actualiseSizeHealthBarOut();

        //create the name of the player under the healthBar
        sf::Text createNamePlayer(Player player, Position posHealthBar);
};

#endif // HEALTHBARVIEW_H
