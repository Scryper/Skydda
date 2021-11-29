#include "PlayerSprite.h"


PlayerSprite::PlayerSprite():sf::Sprite() {

}
PlayerSprite::PlayerSprite(sf::Texture texture):sf::Sprite(texture) {

}
void PlayerSprite::setHitbox(const sf::FloatRect& hitbox) {
    m_hitbox = hitbox;
}
sf::FloatRect PlayerSprite::getGlobalHitbox() const {
    return getTransform().transformRect(m_hitbox);
}
