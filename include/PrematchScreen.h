#ifndef PREMATCHSCREEN_H
#define PREMATCHSCREEN_H

#include "Screen.h"

class PrematchScreen : public Screen {
    private:
        const static inline std::string PATH_IMAGES = "resources/images/";

        const static inline std::string PATH_CHARACTERS = PATH_IMAGES + "characters/";
        const static inline std::string PATH_PREVIEWS = PATH_IMAGES + "previews/";
        const static inline std::string PATH_GAMEMODE = PATH_IMAGES + "gamemode/";

        const static inline std::string PATH_PREVIEW_MAPS = PATH_PREVIEWS + "maps/";
        const static inline std::string PATH_PREVIEW_CHARACTERS = PATH_PREVIEWS + "characters/";

        const static inline std::string PATH_PREVIEW_MAP1 = PATH_PREVIEW_MAPS + "map1_preview.jpg";
        const static inline std::string PATH_PREVIEW_MAP2 = PATH_PREVIEW_MAPS + "map2_preview.jpg";
        const static inline std::string PATH_PREVIEW_MAP3 = PATH_PREVIEW_MAPS + "map3_preview.jpg";

        const static inline std::string PATH_PREVIEW_GOLEM_DARK = PATH_PREVIEW_CHARACTERS + "golem_dark.png";
        const static inline std::string PATH_PREVIEW_GROOT_DARK = PATH_PREVIEW_CHARACTERS + "groot_dark.png";
        const static inline std::string PATH_PREVIEW_MINAUTOR_DARK = PATH_PREVIEW_CHARACTERS + "minotaur_dark.png";

        const static inline std::string PATH_PREVIEW_GOLEM_LIGHT = PATH_PREVIEW_CHARACTERS + "golem_light.png";
        const static inline std::string PATH_PREVIEW_GROOT_LIGHT = PATH_PREVIEW_CHARACTERS + "groot_light.png";
        const static inline std::string PATH_PREVIEW_MINAUTOR_LIGHT = PATH_PREVIEW_CHARACTERS + "minotaur_light.png";

        const static inline std::string PATH_GOLEM_DARK = PATH_CHARACTERS + "golem_dark.png";
        const static inline std::string PATH_GROOT_DARK = PATH_CHARACTERS + "groot_dark.png";
        const static inline std::string PATH_MINAUTOR_DARK = PATH_CHARACTERS + "minotaur_dark.png";

        const static inline std::string PATH_GOLEM_LIGHT = PATH_CHARACTERS + "golem_light.png";
        const static inline std::string PATH_GROOT_LIGHT = PATH_CHARACTERS + "groot_light.png";
        const static inline std::string PATH_MINAUTOR_LIGHT = PATH_CHARACTERS + "minotaur_light.png";

        const static inline std::string PATH_ROUNDS = PATH_GAMEMODE + "rounds.png";
        const static inline std::string PATH_TIMER = PATH_GAMEMODE + "timer.png";

        const static inline std::string NAME_DARK_GOLEM = "Dark Golem";
        const static inline std::string NAME_DARK_GROOT = "Dark Groot";
        const static inline std::string NAME_DARK_MINAUTOR = "Dark Minotaur";

        const static inline std::string NAME_LIGHT_GOLEM = "Light Golem";
        const static inline std::string NAME_LIGHT_GROOT = "Light Groot";
        const static inline std::string NAME_LIGHT_MINAUTOR = "Light Minotaur";

        const static inline std::string TEXT_PREVIOUS = "Previous";
        const static inline std::string TEXT_NEXT = "Next";
        const static inline std::string TEXT_CHOOSE_GAME_MODE = "Choose game mode";
        const static inline std::string TEXT_CHOOSE_MAP = "Choose the map";
        const static inline std::string TEXT_ROUNDS = "Rounds";
        const static inline std::string TEXT_TIME = "Time";

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
        sf::Texture textureGameMode;

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
        sf::Sprite spriteMode;

        Position position;
        Position positionPlayerElements;
        Position positionButtonsMap;
        Position positionTextMap;

        int indexMap = 0;
        int indexCharacter1 = 0;
        int indexCharacter2 = 3;
        int gameMode = 3;

        std::vector<std::string> maps;
        std::vector<std::string> characters;
        std::vector<std::string> names;
        std::vector<std::string> spriteSheets;
        std::vector<std::string> gameModes;
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
