#include "PlayerSprite.h"



void PlayerSprite::setHitbox(const sf::FloatRect& hitbox) {
    m_hitbox = hitbox;
}
sf::FloatRect PlayerSprite::getGlobalHitbox() const {
    return getTransform().transformRect(m_hitbox);
}
