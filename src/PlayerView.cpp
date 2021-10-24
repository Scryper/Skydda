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

bool PlayerView::movePlayer(sf::Vector2f vectorDirection, bool looksRight) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.x < 0) || (!looksRight && vectorDirection.x > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }
    //std::cout << "test 1" << std::endl;
    // calculating the new position of the player
    Position newPosition = player.getMovement() // probleme
                                 .updatePosition(
                                        player.getPosition(),
                                        vectorToCouple(vectorDirection)
                                 );

    //std::cout << "test 2" << std::endl;
    // updating the position info
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

    return looksRight;
}
