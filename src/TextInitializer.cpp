#include "TextInitializer.h"

sf::Text createText(std::string textContent, Position position) {
    sf::Text text;
    text.setString(textContent);
    text.setCharacterSize(24);
    text.setFillColor({253, 240, 213});
    text.setStyle(sf::Text::Bold);

    auto positionX = position.getX();
    auto positionY = position.getY();
    text.setPosition(positionX, positionY);

    return text;
}