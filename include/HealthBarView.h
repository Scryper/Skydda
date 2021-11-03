#ifndef HEALTHBARVIEW_H
#define HEALTHBARVIEW_H
#include <SFML/Graphics.hpp>
#include "HealthBar.h"

class HealthBarView {
    private:
        HealthBar healthBar;
        sf::RectangleShape healthBarIn;
        sf::RectangleShape healthBarOut;

    public:
        HealthBarView();
        HealthBarView(HealthBar healthBar, sf::RectangleShape healthBarIn, sf::RectangleShape healthBarOut);
        virtual ~HealthBarView();
        HealthBarView(const HealthBarView& other);

};

#endif // HEALTHBARVIEW_H
