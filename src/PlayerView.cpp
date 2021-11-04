#include "PlayerView.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right) {
    this->sprite = sprite;
    this->player = player;
    this->up = up;
    this->left = left;
    this->right = right;
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

Position PlayerView::computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<int>> collisions){
    return player.updatePosition(player.getPosition(), vectorToCouple(vectorDirection), collisions);
}

bool PlayerView::movePlayer(sf::Vector2f vectorDirection, bool looksRight, std::vector<std::vector<int>> collisions) {
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

sf::Vector2f PlayerView::inputPlayer(float deltaTime){
     sf::Vector2f vector2f(0.f, 0.f);
        if(sf::Keyboard::isKeyPressed(up)) {
            vector2f.y += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(left)) {
            vector2f.x += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(right)) {
            vector2f.x += deltaTime;
        }
    return vector2f;
}

//void PlayerView::attack(PlayerView playerAttacked){
    //vérif que le player ne bloque pas l'attaque

    //vérif que les pv sont supérieur a 0

    //faire l'animation d'attaque
    //retirer les PV

    //delai????
//}

