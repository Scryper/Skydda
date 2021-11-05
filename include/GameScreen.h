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

        vector<PlatformView> platforms;

        sf::Sprite backgroundSprite;
        sf::Texture textureBackground;
        sf::Texture textureBrick;
        sf::Texture texturePlayerP1;
        sf::Texture texturePlayerP2;
        sf::Font font;
        sf::Text namePlayerP1;
        sf::Text namePlayerP2;

        Game game;
        MapView map1;

        std::vector<sf::CircleShape> roundCirclesP1;
        std::vector<sf::CircleShape> roundCirclesP2;


    public:
        virtual int run(sf::RenderWindow &app);
        void createRoundCircles();
        void actualiseRoundCircles();
        std::vector<sf::CircleShape> getRoundCirclesP1();
        std::vector<sf::CircleShape> getRoundCirclesP2();
        void initPlayers();
        void initMap();
        void initHealthBars();
        void movePlayers(float deltaTime);
        void playerUpdate();
        Game& getGame();
};

#endif // GAMESCREEN_H
