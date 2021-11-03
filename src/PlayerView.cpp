#include "PlayerView.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
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

void PlayerView::stopX(){
    this->player.stopX();
}

void PlayerView::stopY(){
    this->player.stopY();
}

Position PlayerView::computeNewPosition(sf::Vector2f vectorDirection, std::vector<int> collisions){
    return player.updatePosition(player.getPosition(), vectorToCouple(vectorDirection), collisions);
}

bool PlayerView::movePlayer(sf::Vector2f vectorDirection, bool looksRight, std::vector<int> collisions) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.x < 0) || (!looksRight && vectorDirection.x > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

    return looksRight;
}
