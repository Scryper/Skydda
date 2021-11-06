#include "Screen.h"

sf::Vector2f Screen::getMousePosition(sf::RenderWindow *app) const {
    return app->mapPixelToCoords(sf::Mouse::getPosition(*app));
}

// Calculates the ce ter of the screen if it has not been done, then return a position
// with the calculated coordinates
Position Screen::getScreenCenter(sf::RenderWindow *app) {
    middleScreenX = app->getSize().x / 2.;
    middleScreenY = app->getSize().y / 2.;
    center = {middleScreenX, middleScreenY};
    return center;
}
