#include "PlayerView.h"
#include "Collision.h"
#include "Animation.h"

PlayerView::PlayerView() {
    PlayerSprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
    Animation anim;
    this->animation = anim;
}

PlayerView::PlayerView(PlayerSprite sprite, Player player,std::vector<std::pair<playerStatePriority,sf::Keyboard::Key>> keys,bool looksRight, CoupleFloat scalePlayer) {
    this->sprite = sprite;
    this->player = player;
    this->keys = keys;
    this->looksRight = looksRight;
    this->scalePlayer = scalePlayer;
    Animation anim;
    this->animation = anim;

}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
    this->keys = other.keys;
    this->looksRight = other.looksRight;
    this->scalePlayer = other.scalePlayer;
    Animation anim;
    this->animation = anim;

}

PlayerView::~PlayerView() { }

Player& PlayerView::getPlayer() {
    return player;
}

PlayerSprite PlayerView::getSprite() const {
    return sprite;
}

bool PlayerView::isLooksRigth()const{
    return looksRight;
}

void PlayerView::flipSprite() {
    float previousLeft = sprite.getGlobalHitbox().left;

    sprite.scale(-1.f, 1.f);

    float presentLeft = sprite.getGlobalHitbox().left;
    float diff = previousLeft-presentLeft;

    std::cout<<diff<<std::endl;

    Position p(player.getPosition().getX()+diff, player.getPosition().getY());
    sprite.setPosition(p.getX(), p.getY());
    player.setPosition(p);
}

Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions, bool noTP){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions, noTP);
}

void PlayerView::movePlayer(std::vector<std::vector<std::vector<int>>> collisions, bool noTP) {
    CoupleFloat vectorDirection = computeCoupleMovement();
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0) || (!looksRight && vectorDirection.getX() > 0)) {
        flipSprite();
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions, noTP);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());
}

//actualise la liste des touches pressées
void PlayerView::inputPlayer(){
    std::vector<std::pair<playerStatePriority,sf::Keyboard::Key>> tmp;
    for (auto key : keys){
        if(sf::Keyboard::isKeyPressed(key.second))
            tmp.push_back(key);
    }
    keysPressed = tmp;
}

//envoie l'état en fonction de la touche
std::vector<playerStatePriority> PlayerView::getStatesFromInput(){
    inputPlayer();
    std::vector<playerStatePriority> tmp;
    //on parcourt les touches du perso
    for(auto i : keysPressed){
        tmp.push_back(i.first);
    }
    return tmp;
}


CoupleFloat PlayerView::computeCoupleMovement(){
    //affichage des états
    std::vector<playerStatePriority> tmp = getStatesFromInput();
    PlayerStateBoolArray etatsTmp =player.computeStates(tmp);

    for(auto i : etatsTmp){
       std::cout<< i->first << " " <<i->second <<endl;
    }


    state = 4;
    inputPlayer();
    CoupleFloat couple(0.f, 0.f);
    int deltaTime = 1;
    for (auto key : keysPressed) {
        //up
        if(key.second == keys[0].second) {
            state = 5;
            couple.setY(couple.getY() - deltaTime);
        }
        //left
        if(key.second == keys[1].second) {
            state = 6;
            couple.setX(couple.getX() - deltaTime);
        }
        //rigth
        if(key.second == keys[2].second) {
            state = 6;
            couple.setX(couple.getX() + deltaTime);
        }
    }
    return couple;
}

void PlayerView::updateState(PlayerView &playerView){
    inputPlayer();
    //protect
    if(sf::Keyboard::isKeyPressed(keys[4].second)){
        player.setState(defending,true);
    } else {
        player.setState(defending,false);
    }
    //attack
    if(sf::Keyboard::isKeyPressed(keys[3].second)){
        state = 1;
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

void PlayerView::setState(int state) {
    this->state = state;
}

void PlayerView::animate(){
    animation.startAnimation(&this->sprite, this->state);
}

void PlayerView::computeFrame(){

    //compute states
    std::vector<playerStatePriority> statesFromInput = getStatesFromInput();
    PlayerStateBoolArray playerStates =player.computeStates(statesFromInput);

    //parcourir les états
    //for (auto state : statesFromInput){

    //}

        //regarder si l'état est validé
            //si oui,
                //vérif si c'est le premier état
                    //oui faire l'anim => retenir que c'est le premier état
                //est ce qu'il est timed
                    //timed :  y a un timer?
                        //ya un timer
                            //timer dépasser la durée de l'action?
                                //non => vérif si l'action
                        //pas de timer
                            //en créer un
                    //timed : il n'y a pas de timer
}
