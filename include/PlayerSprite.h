#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>
/*
This class is inherited from sf::Sprite to add an hitbox to it and manage the collisions of the players without relying on the size of the texture.
*/
class PlayerSprite : public sf::Sprite {
    public:
        PlayerSprite();
        PlayerSprite(sf::Texture& texture);
        PlayerSprite(const PlayerSprite& other);
        PlayerSprite& operator=(const PlayerSprite& other);

        //used to set the hitbox.
        void setHitbox(const sf::FloatRect& hitbox);

        //used to get the global bounds of the hitbox.
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect m_hitbox;
};

#endif // PLAYERSPRITE_H
