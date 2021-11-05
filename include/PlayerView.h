#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"
#include "CoupleVectorTransformer.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class PlayerView {
    private:
        sf::Sprite sprite;
        Player player;
        sf::Keyboard::Key up;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
        sf::Keyboard::Key attackKey;
        sf::Keyboard::Key protectKey;
        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        int tour;
        int lastState;
        bool looksRight;

    public:
        PlayerView();
        PlayerView(sf::Sprite sprite, Player player, sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key attackKey, sf::Keyboard::Key protectKey);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player& getPlayer();
        sf::Sprite getSprite() const;

        void attack(PlayerView &playerAttacked);
        void setHealth(float health);
        void setAlive(bool alive);

        bool isLooksRigth()const;

        sf::Vector2f inputPlayer(float deltaTime, PlayerView &player2);

        Position computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        void movePlayer(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);

        void animate(int state, int maxFrame);
};

#endif // PLAYERVIEW_H
