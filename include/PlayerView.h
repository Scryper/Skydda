#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Player.h"

#include <SFML/Graphics.hpp>

using namespace std;

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

        void movePlayer(sf::Vector2f vectorDirection);
};

#endif // PLAYERVIEW_H
