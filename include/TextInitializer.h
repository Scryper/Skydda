#ifndef TEXTINITIALIZER_H
#define TEXTINITIALIZER_H

#include <SFML/Graphics.hpp>
#include "Position.h"

class TextInitializer {
    public:
        /// Colors of texts
        static inline sf::Color betterWhite = {253, 240, 213};
        static inline sf::Color betterRed = {193, 18, 31};
        static inline sf::Color darkerBetterRed = {120, 0, 0};

        static sf::Text createText(std::string textContent, Position position);
};

#endif // TEXTINITIALIZER_H
