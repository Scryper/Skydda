#include "PlayerSprite.h"

PlayerSprite::PlayerSprite():sf::Sprite() { }

PlayerSprite::PlayerSprite(sf::Texture& texture):sf::Sprite(texture) { }

void PlayerSprite::setHitbox(const sf::FloatRect& hitbox_) {
    this->hitbox = hitbox_;
}

sf::FloatRect PlayerSprite::getGlobalHitbox() const {
    return getTransform().transformRect(this->hitbox);
}
