#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>

class PlayerSprite : public sf::Sprite {
    private:
        sf::FloatRect hitbox;

    public:
        PlayerSprite();
        PlayerSprite(sf::Texture& texture);

        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;
};

#endif // PLAYERSPRITE_H
