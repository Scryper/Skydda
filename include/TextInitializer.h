#ifndef TEXTINITIALIZER_H
#define TEXTINITIALIZER_H

#include <SFML/Graphics.hpp>
#include "Position.h"

/*
Used to initialize the text in the game
*/
class TextInitializer {
    public:
        /// Colors of texts
        static inline sf::Color BetterWhite = {253, 240, 213};
        static inline sf::Color BetterRed = {193, 18, 31};
        static inline sf::Color DarkerBetterRed = {120, 0, 0};
        static inline sf::Color BetterGrey = {108, 117, 125};

        //create a text with a position
        static sf::Text createText(std::string textContent, Position position);
        static sf::Text createText(std::string textContent, float x, float y);

        //apply the font to a vector of text
        static void initFont(std::vector<sf::Text*> texts, sf::Font* font);

        //apply the font to a text
        static void initFont(sf::Text*, sf::Font* font);
};

#endif // TEXTINITIALIZER_H
