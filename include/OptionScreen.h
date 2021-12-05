#ifndef OPTIONSCREEN_H
#define OPTIONSCREEN_H

#include "Screen.h"
#include "GlobalVariables.h"
#include "MusicManager.h"

class OptionScreen : public Screen {
    private:
        sf::Font font;

        sf::Text textBack;
        sf::Text textValueOfVolume;

        sf::Texture textureBackground;
        sf::Texture textureButton;
        sf::Texture textureButtonPlusMinus;

        sf::Texture textureControlsP1;
        sf::Texture textureControlsP2;

        sf::Sprite backgroundSprite;
        sf::Sprite buttonBack;
        sf::Sprite buttonPlus;
        sf::Sprite buttonMinus;

        sf::Sprite spriteControlsP1;
        sf::Sprite spriteControlsP2;

        Position position;

        MusicManager* musicManager = MusicManager::getInstance();

        std::vector<sf::Text*> texts;

        void initFonts();
        void initBackground();
        void changeVolume(float value);

    public:
        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // OPTIONSCREEN_H
