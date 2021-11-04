#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"
#include "CoupleVectorTransformer.h"
#include "Animate.h"

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
        sf::Texture texture;
        sf::IntRect rectSourceSprite;
        sf::Clock clock;
        int tour;



    public:
        PlayerView();
        PlayerView(sf::Sprite sprite, Player player, sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key attackKey);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player getPlayer() const;
        sf::Sprite getSprite() const;


        void attack(PlayerView &playerAttacked);

        void setHealth(float health);


        sf::Vector2f inputPlayer(float deltaTime, PlayerView &player2);

        Position computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions);
        bool movePlayer(sf::Vector2f vectorDirection, bool looksRight, std::vector<std::vector<std::vector<int>>> collisions);
};

#endif // PLAYERVIEW_H
