#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"

#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "Animation.h"
#include "StatePlayer.h"
#include "SoundManager.h"

class PlayerView {
    private:
        PlayerSprite sprite;
        Player player;
        Animation animation;

        std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keys;
        std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keysPressed;

        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        bool looksRight;
        CoupleFloat scalePlayer;

        SoundManager* soundManager = SoundManager::getInstance();

    public:
        PlayerView();
        PlayerView(PlayerSprite sprite, Player player, std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keys, bool looksRight, CoupleFloat scalePlayer);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        PlayerSprite getSprite() const;

        void attack(PlayerView &playerAttacked, bool left);
        void setHealth(float health);

        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;
        void getHit(int value);

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        void movePlayer(std::vector<std::vector<std::vector<int>>> collisions, PlayerStateEnum state);
        std::vector<PlayerStateEnum> getStatesFromInput();
        bool isBottomCollision(std::vector<std::vector<std::vector<int>>> coll);

        void animate(bool first,PlayerStateEnum state, bool boucle);
        void flipSprite();
        void computeFrame(std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView);
        void doAction(PlayerStateEnum state,std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView);
};

#endif // PLAYERVIEW_H
