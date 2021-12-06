#include "PlayerSprite.h"

PlayerSprite::PlayerSprite():sf::Sprite() { }

PlayerSprite::PlayerSprite(sf::Texture& texture):sf::Sprite(texture) { }

PlayerSprite::PlayerSprite(const PlayerSprite& other):sf::Sprite(other) {
        this->m_hitbox = other.m_hitbox;
}

PlayerSprite& PlayerSprite::operator=(const PlayerSprite& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    sf::Sprite::operator=(rhs);
    this->m_hitbox = rhs.m_hitbox;
    return *this;
}

//set the hitbox.
void PlayerSprite::setHitbox(const sf::FloatRect& hitbox) {
    m_hitbox = hitbox;
}

//get the global bounds of the hitbox.
sf::FloatRect PlayerSprite::getGlobalHitbox() const {
    return getTransform().transformRect(m_hitbox);
}
