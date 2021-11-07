#include "PlayerView.h"
#include "Collision.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,std::vector<sf::Keyboard::Key> keys,bool looksRight, CoupleFloat scalePlayer, std::vector<std::vector<float>> offsetState) {
    this->sprite = sprite;
    this->player = player;
    this->keys = keys;
    this->looksRight = looksRight;
    this->scalePlayer = scalePlayer;
    this->offsetState = offsetState;
}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
    this->keys = other.keys;
    this->looksRight = other.looksRight;
    this->scalePlayer = other.scalePlayer;
    this->offsetState = other.offsetState;
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

std::vector<std::vector<float>> PlayerView::getOffset()const{
        return offsetState;
}

bool PlayerView::isLooksRigth()const{
    return looksRight;
}

void PlayerView::flipSprite() {
    sprite.setScale(-scalePlayer.getX(), scalePlayer.getY());
}

Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool osef){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions, osef);
}

void PlayerView::movePlayer(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool osef) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0) || (!looksRight && vectorDirection.getX() > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions, osef);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());
}

//actualise la liste des touches pressées
void PlayerView::inputPlayer(){
    std::vector<sf::Keyboard::Key> tmp;
    if(player.isAlive()){
        for (sf::Keyboard::Key key : keys){
            if(sf::Keyboard::isKeyPressed(key))
                tmp.push_back(key);
        }
    }
    keysPressed = tmp;
}

CoupleFloat PlayerView::computeCoupleMovement(){
    state = 4;
    maxFrame = 12;

    inputPlayer();
    CoupleFloat couple(0.f, 0.f);
    int deltaTime = 1;
    for (sf::Keyboard::Key key : keysPressed) {
        //up
        if(key == keys[0]) {
            state = 5;
            maxFrame = 6;
            couple.setY(couple.getY() - deltaTime);
        }
        //left
        if(key == keys[1]) {
            state = 6;
            maxFrame = 12;
            couple.setX(couple.getX() - deltaTime);
        }
        //rigth
        if(key == keys[2]) {
            state = 6;
            maxFrame = 12;
            couple.setX(couple.getX() + deltaTime);
        }
    }
    return couple;
}

void PlayerView::updateState(PlayerView &playerView){
    inputPlayer();
    //protect
    if(sf::Keyboard::isKeyPressed(keys[4])){
        player.setDefense(true);
    } else {
        player.setDefense(false);
    }
    //attack
    if(sf::Keyboard::isKeyPressed(keys[3])){
        state = 1;
        maxFrame = 12;
        //vérif s'il y a une collision, si oui on peut lancer l'appel de la fonction
        //la direction de l'attaque n'est gérée
        std::vector<std::vector<int>> collision = directionCollisionPlayers(*this, playerView);
        if(collision.size() > 0 && collision[0][0] > 0){
            for(auto i : collision){
                if((i[0] == 3 && !looksRight) || (i[0] == 4 && looksRight)) {
                    attack(playerView);
                }
            }
        }
    }
}

void PlayerView::attack(PlayerView &playerAttacked){
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds());

    playerAttacked.setMaxFrame(12);
    if(playerAttacked.getPlayer().getHealth() != 0.f){
        playerAttacked.setState(3);
    }
    else{
        playerAttacked.setState(2);
    }
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

void PlayerView::setMaxFrame(int maxFrame) {
    this->maxFrame = maxFrame;
}

void PlayerView::setState(int state) {
    this->state = state;
}

void PlayerView::animate()
{
    float x = this->sprite.getOrigin().x * 2;
    float y = this->sprite.getOrigin().y * 2;

    this->maxFrame -= 1;
    if (this->clock.getElapsedTime().asMilliseconds() % 3 == 0){

        if (this->tour == this->maxFrame || (this->lastState != this->state && (this->lastState != 1 && this->lastState != 3))){
            this->tour = 0;
        }
        else{
            this->tour += 1;
        }

        if((this->lastState != 3 && this->lastState != 1) || (tour == 0 && (lastState == 1 || lastState == 3)))
        {
        this->lastState = this->state;
        }

        this->sprite.setTextureRect(sf::IntRect(this->tour * x, (this->lastState-1) * y, x, y));

    }
}
