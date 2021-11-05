#ifndef TEXTINITIALIZER_H
#define TEXTINITIALIZER_H

#include <SFML/Graphics.hpp>
#include "Position.h"

class TextInitializer {
    public:
        /// Colors of texts
        static inline sf::Color BetterWhite = {253, 240, 213};
        static inline sf::Color BetterRed = {193, 18, 31};
        static inline sf::Color DarkerBetterRed = {120, 0, 0};
        static inline sf::Color BetterGrey = {108, 117, 125};

        static sf::Text createText(std::string textContent, Position position);
};

#endif // TEXTINITIALIZER_H
