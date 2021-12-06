#include "PlayerSprite.h"

PlayerSprite::PlayerSprite():sf::Sprite() { }

PlayerSprite::PlayerSprite(sf::Texture& texture):sf::Sprite(texture) { }

void PlayerSprite::setHitbox(const sf::FloatRect& hitbox_) {
    this->hitbox = hitbox_;
}

PlayerSprite& PlayerSprite::operator=(const PlayerSprite& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    sf::Sprite::operator=(rhs);
    this->hitbox = rhs.hitbox;
    return *this;
}

void PlayerSprite::setHitbox(const sf::FloatRect& hitbox_) {
    this->hitbox = hitbox_;
}

sf::FloatRect PlayerSprite::getGlobalHitbox() const {
    return getTransform().transformRect(this->hitbox);
}
