#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <SFML/Graphics.hpp>



class PlayerSprite : public sf::Sprite
{
    public:
        PlayerSprite();
        PlayerSprite(sf::Texture texture);

        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;

    protected:

    private:
        sf::FloatRect m_hitbox;

};

#endif // PLAYERSPRITE_H
