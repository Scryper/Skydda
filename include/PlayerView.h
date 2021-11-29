#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"
#include "CoupleVectorTransformer.h"

#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"

class PlayerView {
    private:
        PlayerSprite sprite;
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
        int state;
        int maxFrame;
        bool looksRight;
        CoupleFloat scalePlayer;

    public:
        PlayerView();
        PlayerView(PlayerSprite sprite, Player player, std::vector<sf::Keyboard::Key> keys, bool looksRight, CoupleFloat scalePlayer);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        PlayerSprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);
        void setAlive(bool alive);
        void setState(int state);
        void setMaxFrame(int maxFrame);

        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool noTP);
        void movePlayer(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool noTP);
        void updateState(PlayerView &playerView);

        void animate();
        void flipSprite();
};

#endif // PLAYERVIEW_H
