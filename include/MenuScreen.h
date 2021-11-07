#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"

class MenuScreen : public Screen {
    private:
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
