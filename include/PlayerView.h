#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"
#include "CoupleVectorTransformer.h"

#include <SFML/Graphics.hpp>

class PlayerView {
    private:
        sf::Sprite sprite;
        Player player;

        //0 : up
        //1 : left
        //2 : rigth
        //3 : attack
        //4 : protect
        std::vector<sf::Keyboard::Key> keys;
        std::vector<sf::Keyboard::Key> keysPressed;

        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        int tour;
        int lastState;
        bool looksRight;
        CoupleFloat scalePlayer;

    public:
        PlayerView();
        PlayerView(sf::Sprite sprite, Player player, std::vector<sf::Keyboard::Key> keys, bool looksRight, CoupleFloat scalePlayer);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        sf::Sprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);
        void setAlive(bool alive);


        bool isLooksRigth()const;

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        void movePlayer(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        void updateState(PlayerView &playerView);

        void animate(int state, int maxFrame);
        void flipSprite();
};

#endif // PLAYERVIEW_H
