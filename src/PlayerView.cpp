#include "PlayerView.h"
#include "Collision.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right,sf::Keyboard::Key attack, sf::Keyboard::Key protect) {
    this->sprite = sprite;
    this->player = player;
    this->up = up;
    this->left = left;
    this->right = right;
    this->attackKey = attack;
    this->protectKey = protect;
    this->looksRight = true;
}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
}

PlayerView::~PlayerView() { }

Player& PlayerView::getPlayer() {
    return player;
}

sf::Sprite PlayerView::getSprite() const {
    return sprite;
}

void PlayerView::setAlive(bool alive) {
    player.setAlive(alive);
}

bool PlayerView::isLooksRigth()const{
    return looksRight;
}

Position PlayerView::computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions){
    return player.updatePosition(player.getPosition(), vectorToCouple(vectorDirection), collisions);
}

void PlayerView::movePlayer(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.x < 0) || (!looksRight && vectorDirection.x > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

}

sf::Vector2f PlayerView::inputPlayer(float deltaTime, PlayerView &p2){
    int state = 3;
    int maxFrame = 3;
     sf::Vector2f vector2f(0.f, 0.f);

     if(player.isAlive()) {

        if(sf::Keyboard::isKeyPressed(up)) {
            vector2f.y += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(left)) {
            state = 7;
            maxFrame = 10;
            vector2f.x += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(right)) {
            state = 7;
            maxFrame = 10;
            vector2f.x += deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(protectKey)){
            player.setDefense(true);
        }else{
            player.setDefense(false);
        }
        if(sf::Keyboard::isKeyPressed(attackKey)){
            //vérif s'il y a une collision, si oui on peut lancer l'appel de la fonction
            //la direction de l'attaque n'est gérée
            std::vector<std::vector<int>> collision = directionCollisionPlayers(*this,p2);
            if(collision.size()>0 && collision[0][0]>0){
                for(auto i : collision){
                    if((i[0]==3 && !looksRight) || (i[0]==4 && looksRight)){
                        attack(p2);
                    }
                }
            }
        }
    }
    animate(state,maxFrame);
    return vector2f;
}

void PlayerView::attack(PlayerView &playerAttacked){
    //vérif que le player ne bloque pas l'attaque
    if(playerAttacked.getPlayer().getDefense()==true)
        return;
    //vérif que les pv sont supérieur a 0
    if(playerAttacked.getPlayer().getHealth()<=0)
        return;
    //faire l'animation d'attaque

    //retirer les PV
    double health = playerAttacked.player.getHealth();
    if(health-player.getAttack()>0){
        playerAttacked.player.setHealth(health-player.getAttack());
    }
    else{
        playerAttacked.player.setHealth(0.f);
    }

    //delai????
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

void PlayerView::animate(int state, int maxFrame)
{
    float x = this->sprite.getOrigin().x * 2;
    float y = this->sprite.getOrigin().y * 2;

    maxFrame -= 1;
    if (this->clock.getElapsedTime().asMilliseconds() % 10 == 0){

        if (this->tour == maxFrame || state != lastState){
            this->tour = 0;
        }
        else{
            this->tour += 1;
        }
        lastState = state;
        this->sprite.setTextureRect(sf::IntRect(tour * x, state * y, x, y));
        //this->clock.restart();

    }
}
