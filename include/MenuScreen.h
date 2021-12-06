#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"

class MenuScreen : public Screen {
    private:
        const static inline std::string PATH_BACKGROUND = "resources/images/background/background_menu.jpg";

        const static inline std::string TEXT_OPTIONS = "Options";
        const static inline std::string TEXT_QUIT = "Quit";

        Position position;

        sf::Font font;

        sf::Text textChooseCharacters;
        sf::Text textOptions;
        sf::Text textQuit;

        sf::Texture textureBackground;
        sf::Texture textureButton; // Button texture

        sf::Sprite background;
        sf::Sprite buttonChooseCharacters;
        sf::Sprite buttonOptions;
        sf::Sprite buttonQuit;

        std::vector<sf::Text*> texts;

        void initBackground();
        void initFonts();

    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // MENUSCREEN_H
