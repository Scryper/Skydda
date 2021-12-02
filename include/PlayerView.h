#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"
#include "CoupleVectorTransformer.h"

#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "Animation.h"
#include "StatePlayer.h"

class PlayerView {
    private:
        PlayerSprite sprite;
        Player player;
        Animation animation;

        std::vector<std::pair<playerStatePriority,sf::Keyboard::Key>> keys;
        std::vector<std::pair<playerStatePriority,sf::Keyboard::Key>> keysPressed;

        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        int state;
        bool looksRight;
        CoupleFloat scalePlayer;

    public:
        PlayerView();
        PlayerView(PlayerSprite sprite, Player player, std::vector<std::pair<playerStatePriority,sf::Keyboard::Key>> keys, bool looksRight, CoupleFloat scalePlayer);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        PlayerSprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);
        void setState(int state);

        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool noTP);
        void movePlayer(std::vector<std::vector<std::vector<int>>> collisions, bool noTP);
        void updateState(PlayerView &playerView);
        std::vector<playerStatePriority> getStatesFromInput();

        void animate();
        void flipSprite();
        void computeFrame();
};

#endif // PLAYERVIEW_H
