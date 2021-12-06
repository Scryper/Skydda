#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "SpriteInitializer.h"
#include "TextInitializer.h"

class Screen {
    private:
        int middleScreenX;
        int middleScreenY;

        Position center;

    protected:
        const static inline std::string PATH_BACKGROUND_OTHER = "resources/images/background/background_other.jpg";
        const static inline std::string PATH_BUTTON = "resources/images/buttons/button.png";
        const static inline std::string PATH_FONT = "resources/fonts/glitch.otf";

        const static inline std::string TEXT_PLAY = "Play";
        const static inline std::string TEXT_BACK = "Back";

        sf::Event event;

        sf::Vector2f mousePosition;

    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed) = 0;

        sf::Vector2f getMousePosition(sf::RenderWindow *app) const;
        Position getScreenCenter(sf::RenderWindow *app);
};

#endif // SCREEN_H
