#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"

#include <SFML/Graphics.hpp>
#include "PlayerSprite.h"
#include "Animation.h"
#include "StatePlayer.h"
#include "SoundManager.h"
#include "EnumCollision.h"

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

        SoundManager* soundManager = SoundManager::getInstance();

    public:
        PlayerView();
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);
        PlayerView& operator=(const PlayerView& other);


        void setHealth(float health);
        void setLooksRigth(bool right);
        void setSprite(PlayerSprite sprite_);
        void setPlayer(Player player_);
        void setKeys(std::vector<pair<PlayerStateEnum,sf::Keyboard::Key>> keys_);

        Player& getPlayer();
        PlayerSprite getSprite() const;
        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;

        void getHit(int value);
        std::vector<PlayerStateEnum> getStatesFromInput();
        bool isBottomCollision(std::vector<CollisionVector> coll);

        void attack(PlayerView &playerAttacked, bool left, float factor);
        void movePlayer(std::vector<CollisionVector> collisions, PlayerStateEnum state);
        void animate(bool first,PlayerStateEnum state, bool boucle);
        void flipSprite();
        void computeFrame(std::vector<CollisionVector> collisions, PlayerView &playerView);
        void doAction(PlayerStateEnum state,std::vector<CollisionVector> collisions, PlayerView &playerView, bool doActionNow);
        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<CollisionVector> collisions);
        CoupleFloat computeCoupleMovement();
        void inputPlayer();
};

#endif // PLAYERVIEW_H
