#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "PlayerView.h"
#include "PlatformView.h"
#include "Collision.h"
#include "ObjectInitializer.h"
#include "MapView.h"
#include "HealthBar.h"
#include "HealthBarView.h"
#include "Game.h"

class GameScreen : public Screen {
    private:
        Position position;
        Position positionP1;
        Position positionP2;

        HealthBarView healthBarViewP1;
        HealthBarView healthBarViewP2;

        PlayerView playerViewP1;
        PlayerView playerViewP2;

        sf::Sprite backgroundSprite;

        sf::Texture textureBackground;
        sf::Texture textureBrick;
        sf::Texture texturePlayerP1;
        sf::Texture texturePlayerP2;
        sf::Texture texturePlatformGround;
        sf::Texture texturePlatformLong;
        sf::Texture texturePlatformSmall;
        sf::Texture texturePlatformTiny;

        sf::Font font;

        sf::Text namePlayerP1;
        sf::Text namePlayerP2;

        sf::Text textAnimation;

        Game game;
        MapView map_;

        std::vector<sf::CircleShape> roundCirclesP1;
        std::vector<sf::CircleShape> roundCirclesP2;
        std::vector<sf::Texture*> textures;
        std::vector<PlatformView> platforms;

        std::string playerName1;
        std::string spriteSheet1;
        std::string playerName2;
        std::string spriteSheet2;

        int mapSeed;

    public:
        int run(sf::RenderWindow &app, std::vector<std::string> data, int seed);

        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();

        virtual sf::Text displayAnimations(sf::Time timer, sf::RenderWindow &app)=0;

        void createRoundCircles();
        void actualiseRoundCircles();
        void initPlayers();
        void initSprites();
        void initTextures();
        void initVectors();
        void initMap();
        void initHealthBars();
        void movePlayers(float deltaTime, bool noTP);
        void playerUpdate();
        void clearRoundCircles();

        void setAnimationText(sf::Time timer,sf::RenderWindow &app);


        Game& getGame();
};

#endif // GAMESCREEN_H
