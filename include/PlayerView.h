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

    public:
        PlayerView();
        PlayerView(sf::Sprite sprite, Player player);
        virtual ~PlayerView();
        PlayerView(const PlayerView& other);

        Player getPlayer() const;
        sf::Sprite getSprite() const;

        void stopX();
        void stopY();

        Position computeNewPosition(sf::Vector2f vectorDirection, int collision);
        bool movePlayer(sf::Vector2f vectorDirection, bool looksRight, int collision);
};

#endif // PLAYERVIEW_H
