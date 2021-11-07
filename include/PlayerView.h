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

        //
        std::vector<std::vector<float>> offsetState;

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
        PlayerView(sf::Sprite sprite, Player player, std::vector<sf::Keyboard::Key> keys, bool looksRight, CoupleFloat scalePlayer,std::vector<std::vector<float>> offsetState);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        sf::Sprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);
        void setAlive(bool alive);
        void setState(int state);
        void setMaxFrame(int maxFrame);

        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool osef);
        void movePlayer(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool osef);
        void updateState(PlayerView &playerView);

        void animate();
        void flipSprite();
};

#endif // PLAYERVIEW_H
