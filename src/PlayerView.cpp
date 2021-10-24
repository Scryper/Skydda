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

bool PlayerView::movePlayer(sf::Vector2f vectorDirection, bool looksRight) {



    if( (looksRight && vectorDirection.x < 0) || (!looksRight && vectorDirection.x > 0) ) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight;
    }
    //std::cout << "test 1" << std::endl;
    Position newPosition = player.getMovement() // probleme
                                 .updatePosition(
                                        player.getPosition(),
                                        vectorToCouple(vectorDirection)
                                 );

    //std::cout << "test 2" << std::endl;
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

    return looksRight;
}
