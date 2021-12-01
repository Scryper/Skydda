#ifndef PREMATCHSCREEN_H
#define PREMATCHSCREEN_H

#include "Screen.h"

class PrematchScreen : public Screen {
    private:
        sf::Event event;

        sf::Font font;

        sf::Vector2f mousePosition;

        sf::Text firstPlayerName;
        sf::Text textFirstPlayerPrevious;
        sf::Text textFirstPlayerNext;
        sf::Text textValidateFirstPlayer;
        sf::Text secondPlayerName;
        sf::Text textSecondPlayerPrevious;
        sf::Text textSecondPlayerNext;
        sf::Text textValidateSecondPlayer;
        sf::Text textMap;
        sf::Text textPreviousMap;
        sf::Text textNextMap;
        sf::Text textPlay;
        sf::Text textBack;
        sf::Text textMode;
        sf::Text textModeRounds;
        sf::Text textModeTime;

        sf::Texture textureBackground;
        sf::Texture textureButton;
        sf::Texture textureCharacter1;
        sf::Texture textureCharacter2;
        sf::Texture textureMap;

        sf::Sprite backgroundSprite;
        sf::Sprite spriteCharacter1;
        sf::Sprite spriteCharacter2;
        sf::Sprite buttonFirstPlayerPrevious;
        sf::Sprite buttonFirstPlayerNext;
        sf::Sprite buttonSecondPlayerPrevious;
        sf::Sprite buttonSecondPlayerNext;
        sf::Sprite buttonValidateSecondPlayer;
        sf::Sprite spriteMap;
        sf::Sprite buttonPreviousMap;
        sf::Sprite buttonNextMap;
        sf::Sprite buttonPlay;
        sf::Sprite buttonBack;
        sf::Sprite buttonModeRounds;
        sf::Sprite buttonModeTime;

        Position position;
        Position positionPlayerElements;
        Position positionButtonsMap;
        Position positionTextMap;

        int indexMap = 0;
        int indexCharacter1 = 0;
        int indexCharacter2 = 3;
        int gameMode = 2;

        std::vector<std::string> maps;
        std::vector<std::string> characters;
        std::vector<std::string> names;
        std::vector<std::string> spriteSheets;
        std::vector<sf::Text*> texts;

        void initVectors();
        void initBackground();
        void initPositions();
        void initFonts();

    public:
        std::string strFirstPlayerName;
        std::string strSecondPlayerName;
        std::string pathSpriteFirstPlayer;
        std::string pathSpriteSecondPlayer;
        int map_; // Because map is keyword

        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // PREMATCHSCREEN_H
