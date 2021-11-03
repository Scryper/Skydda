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

    public:
        PlayerView();
        PlayerView(sf::Sprite sprite, Player player, sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player getPlayer() const;
        sf::Sprite getSprite() const;

        void stopX();
        void stopY();

        sf::Vector2f inputPlayer(float deltaTime);

        Position computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<int>> collisions);
        bool movePlayer(sf::Vector2f vectorDirection, bool looksRight, std::vector<std::vector<int>> collisions);
};

#endif // PLAYERVIEW_H
