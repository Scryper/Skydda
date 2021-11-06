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
        sf::Text textPreviousMap;
        sf::Text textNextMap;
        sf::Text textPlay;
        sf::Text textBack;

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

        Position position;
        Position positionPlayerElements = {350, 200};
        Position positionButtonsMap = {860, 700};
        Position positionTextMap = {positionButtonsMap.getX() - 75, positionButtonsMap.getY() - 13};

        int indexMap = 0;
        int indexCharacter = 0;

        bool firstPlayerOk = false;
        bool secondPlayerOk = false;

        std::vector<std::string> maps;
        std::vector<std::string> characters;
        std::vector<std::string> names;
        std::vector<std::string> spriteSheets;

        void initVectors();
        void initBackground();

    public:
        std::string strFirstPlayerName;
        std::string strSecondPlayerName;
        std::string pathSpriteFirstPlayer;
        std::string pathSpriteSecondPlayer;
        int map_; // Because map is keyword

        virtual int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);
};

#endif // PREMATCHSCREEN_H
