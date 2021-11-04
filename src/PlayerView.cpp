#include "PlayerView.h"
#include "Collision.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right,sf::Keyboard::Key attack) {
    this->sprite = sprite;
    this->player = player;
    this->up = up;
    this->left = left;
    this->right = right;
    this->attackKey = attack;
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

Position PlayerView::computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions){
    return player.updatePosition(player.getPosition(), vectorToCouple(vectorDirection), collisions);
}

bool PlayerView::movePlayer(sf::Vector2f vectorDirection, bool looksRight, std::vector<std::vector<std::vector<int>>> collisions) {
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

sf::Vector2f PlayerView::inputPlayer(float deltaTime, PlayerView &p2){
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
        if(sf::Keyboard::isKeyPressed(attackKey)){
            //vérif s'il y a une collision, si oui on peut lancer l'appel de la fonction
            //la direction de l'attaque n'est pas encore gérée
            std::vector<std::vector<int>> collision = directionCollisionPlayers(*this,p2);
            if(collision[0][0]>0){
                std::cout<<"attaké  "<< collision[0][0] <<endl;
                attack(p2);

             }
        }
    return vector2f;
}

void PlayerView::attack(PlayerView &playerAttacked){
    cout<<playerAttacked.player.getHealth()<<endl;
    //vérif que le player ne bloque pas l'attaque
    if(playerAttacked.getPlayer().getDefense()==true)
        return;
    //vérif que les pv sont supérieur a 0
    if(playerAttacked.getPlayer().getHealth()<=0)
        return;
    //faire l'animation d'attaque

    //retirer les PV
    double health = playerAttacked.player.getHealth();
    if(health-player.getAttack()>=0){
        playerAttacked.player.setHealth(health-player.getAttack());
    }
    else{
        playerAttacked.player.setHealth(0.f);
    }

    //delai????
}

