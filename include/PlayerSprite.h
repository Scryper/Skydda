#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>

class PlayerSprite : public sf::Sprite {
    public:
        PlayerSprite();
        PlayerSprite(sf::Texture& texture);
        PlayerSprite(const PlayerSprite& other);
        PlayerSprite& operator=(const PlayerSprite& other);


        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect m_hitbox;
};

#endif // PLAYERSPRITE_H
