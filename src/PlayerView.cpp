#include "PlayerView.h"
#include "Collision.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,std::vector<sf::Keyboard::Key> keys,bool looksRight, CoupleFloat scalePlayer) {
    this->sprite = sprite;
    this->player = player;
    this->keys = keys;
    this->looksRight = looksRight;
    this->scalePlayer = scalePlayer;
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

void PlayerView::flipSprite() {
    sprite.setScale(-scalePlayer.getX(), scalePlayer.getY());
}

Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions);
}

void PlayerView::movePlayer(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0) || (!looksRight && vectorDirection.getX() > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

}

//actualise la liste des touches pressées
void PlayerView::inputPlayer(){
    std::vector<sf::Keyboard::Key> temp;
    if(player.isAlive()){
        for (auto i : keys){
            if(sf::Keyboard::isKeyPressed(i))
                temp.push_back(i);
        }
    }
    keysPressed = temp;
}

CoupleFloat PlayerView::computeCoupleMovement(){
    int state = 3;
    int maxFrame = 3;

    inputPlayer();
    CoupleFloat cf(0.f,0.f);
    int deltaTime = 1;
    for (auto i : keysPressed){
        //up
        if(i==keys[0]) {
            cf.setY(cf.getY()-deltaTime);
        }
        //left
        if(i==keys[1]) {
            state = 7;
            maxFrame = 10;
            cf.setX(cf.getX()-deltaTime);
        }
        //rigth
        if(i==keys[2]) {
            state = 7;
            maxFrame = 10;
            cf.setX(cf.getX()+deltaTime);
        }
    }
    animate(state,maxFrame);
    return cf;
}

void PlayerView::updateState(PlayerView &p2){
    inputPlayer();
    //protect
    if(sf::Keyboard::isKeyPressed(keys[4])){
        player.setDefense(true);
    }else{
        player.setDefense(false);
    }
    //attack
    if(sf::Keyboard::isKeyPressed(keys[3])){
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

void PlayerView::attack(PlayerView &playerAttacked){
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds());
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
