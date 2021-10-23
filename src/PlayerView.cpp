#include "PlayerView.h"

PlayerView::PlayerView() {
    sf::Sprite s;
    this->sprite = s;
    Player p;
    this->player = p;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player) {
    this->sprite = sprite;
    this->player = player;
}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
}

PlayerView::~PlayerView() { }

Player PlayerView::getPlayer() const {
    return player;
}

sf::Sprite PlayerView::getSprite() const {
    return sprite;
}

void PlayerView::movePlayer(sf::Vector2f vectorDirection) {
    Position newPosition = player.getMovement()
                                 .updatePosition(
                                        player.getPosition(),
                                        vectorToCouple(vectorDirection)
                                 );
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());
}
