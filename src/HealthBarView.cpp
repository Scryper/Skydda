#include "HealthBarView.h"

HealthBarView::HealthBarView() {
    //ctor
}

HealthBarView::HealthBarView(HealthBar healthBar, sf::RectangleShape healthBarIn, sf::RectangleShape healthBarOut) {
    this->healthBar = healthBar;
    this->healthBarIn = healthBarIn;
    this->healthBarOut = healthBarOut;
}

HealthBarView::~HealthBarView() {
    //dtor
}

HealthBarView::HealthBarView(const HealthBarView& other) {
    //copy ctor
}
