#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>

class PlayerSprite : public sf::Sprite {
    private:
        sf::FloatRect hitbox;

    public:
        PlayerSprite();
        PlayerSprite(sf::Texture& texture);
        PlayerSprite(const PlayerSprite& other);
        PlayerSprite& operator=(const PlayerSprite& other);


        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;
};

#endif // PLAYERSPRITE_H
