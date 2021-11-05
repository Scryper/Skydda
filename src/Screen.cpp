#include "Screen.h"

sf::Vector2f Screen::getMousePosition(sf::RenderWindow *app) const {
    return app->mapPixelToCoords(sf::Mouse::getPosition(*app));
}
