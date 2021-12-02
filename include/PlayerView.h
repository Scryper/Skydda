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

        std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keys;
        std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keysPressed;

        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        bool looksRight;
        CoupleFloat scalePlayer;

    public:
        PlayerView();
        PlayerView(PlayerSprite sprite, Player player, std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keys, bool looksRight, CoupleFloat scalePlayer);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        PlayerSprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);

        std::vector<std::vector<float>> getOffset()const;
        bool isLooksRigth()const;

        void inputPlayer();

        CoupleFloat computeCoupleMovement();

        Position computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        void movePlayer(std::vector<std::vector<std::vector<int>>> collisions, PlayerStateEnum state);
        //void updateState(PlayerView &playerView);
        std::vector<PlayerStateEnum> getStatesFromInput();

        void animate(bool first,PlayerStateEnum state, bool boucle);
        void flipSprite();
        void computeFrame(std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView);
        void doAction(PlayerStateEnum state,std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView);
};

#endif // PLAYERVIEW_H
