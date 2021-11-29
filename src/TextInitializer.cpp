#include "TextInitializer.h"

sf::Text TextInitializer::createText(std::string textContent, Position position) {
    sf::Text text;
    text.setString(textContent);
    text.setCharacterSize(24);
    text.setFillColor(TextInitializer::BetterWhite);
    text.setStyle(sf::Text::Bold);

    auto positionX = position.getX();
    auto positionY = position.getY();
    text.setPosition(positionX, positionY);

    return text;
}

void TextInitializer::initFont(std::vector<sf::Text*> texts, sf::Font* font) {
    for(sf::Text* text : texts) {
        text->setFont(*font);
    }
}

void TextInitializer::initFont(sf::Text* text, sf::Font* font) {
    text->setFont(*font);
}
