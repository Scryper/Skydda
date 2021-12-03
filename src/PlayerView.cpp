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

PlayerView::PlayerView(PlayerSprite sprite, Player player,std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> keys,bool looksRight, CoupleFloat scalePlayer) {
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

Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<std::vector<std::vector<int>>> collisions){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions);
}

void PlayerView::movePlayer(std::vector<std::vector<std::vector<int>>> collisions, PlayerStateEnum state) {
    CoupleFloat vectorDirection = computeCoupleMovement();
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0) || (!looksRight && vectorDirection.getX() > 0)) {
        flipSprite();
        looksRight = !looksRight; // to know where he is looking
    }
    if(state==momentum){
        CoupleFloat tmp(0.f, 0.f);
        vectorDirection = tmp;
    }
    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());
}

//actualise la liste des touches pressées
void PlayerView::inputPlayer(){
    std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> tmp;
    for (auto key : keys){
        if(sf::Keyboard::isKeyPressed(key.second))
            tmp.push_back(key);
    }
    keysPressed = tmp;
}

//envoie l'état en fonction de la touche
std::vector<PlayerStateEnum> PlayerView::getStatesFromInput(){
    inputPlayer();
    std::vector<PlayerStateEnum> tmp;
    //on parcourt les touches du perso
    for(auto i : keysPressed){
        tmp.push_back(i.first);
    }
    return tmp;
}


CoupleFloat PlayerView::computeCoupleMovement(){
    CoupleFloat couple(0.f, 0.f);
    int deltaTime = 1;
    for (auto key : keysPressed) {
        //up
        if(key.second == keys[0].second) {
            couple.setY(couple.getY() - deltaTime);
        }
        //left
        if(key.second == keys[1].second) {
            couple.setX(couple.getX() - deltaTime);
        }
        //rigth
        if(key.second == keys[2].second) {
            //state = 6;
            couple.setX(couple.getX() + deltaTime);
        }
    }
    return couple;
}

void PlayerView::getHit(int value){
    player.getHit(value);
}

void PlayerView::attack(PlayerView &playerAttacked, bool left){
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds());

    //si attaqué changer state
    if(playerAttacked.getPlayer().getHealth() != 0.f){
        playerAttacked.getPlayer().setState(receiveDamage,true);
        //lui donner une vitesse dans le sens du tapage
        playerAttacked.getHit(10.f);
        std::cout<<playerAttacked.getPlayer().getMovement().getSpeed().getX()<<endl;
    }
    else{
        playerAttacked.getPlayer().setState(dead,true);
    }
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

void PlayerView::animate(bool first,PlayerStateEnum state, bool boucle){
    if (first)
    animation.startAnimation(&this->sprite, state, boucle);
}

bool PlayerView::isBottomCollision(std::vector<std::vector<std::vector<int>>> coll){
    for(auto collisions : coll){
        for(auto coteCollision : collisions){
            if(coteCollision[0]==2){
                return true;
            }
        }
    }
    return false;
}


void PlayerView::computeFrame(std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView){

    //compute states
    std::vector<PlayerStateEnum> statesFromInput = getStatesFromInput();
    PlayerStateBoolArray playerStates =player.computeStates(statesFromInput, isBottomCollision(collisions));

    //pour se souvenir de si c'est le premier état => si on doit faire l'animation
    bool firstStateActivated = 0 ;

    //On passe la clock de tous les états non activés a 0
    for (auto state : playerStates){
        if(state->second==0){
            (*animation.getStateClock())[state->first]->second->restart();
        }
    }
    //parcourir les états
    for (auto state : playerStates){
        //regarder si l'état est activé
        if(state->second==1){

            //état timed?
            bool isTimed = constPlayerStates[state->first].isTimed;
            //si l'état est timed
            if(isTimed == 1 ){

                //on récup la clock de létat
                sf::Clock* stateClock = (*animation.getStateClock())[state->first]->second;
                int timeElapsed = stateClock->getElapsedTime().asMilliseconds();
                int timeAction = constPlayerStates[state->first].timeAction;

                //on vérif le timming de l'action, si c'est 0 il faut l'effectuer de suite
                bool actionImmediate = (timeAction==0);
                if(actionImmediate == 1){
                    doAction(state->first, collisions,playerView);
                }
                //action a t > 0
                else{
                    if(timeElapsed>=timeAction&& timeElapsed<=timeAction+16){
                        doAction(state->first, collisions,playerView);
                    }
                }
                //cout<<timeElapsed<<endl;
                if(timeElapsed<15){
                    //cout<<"resetTour"<<endl;
                    animation.resetTour(state->first);
                }

                //si le temps écoulé est trop grand
                if(timeElapsed>=constPlayerStates[state->first].animationDuration){
                    state->second = 0;
                    stateClock->restart();
                    animation.resetTour(state->first);
                }
                else{
                    if(!firstStateActivated)
                        animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
                }


            }
            //state not timed
            else{
                //s'il est joué la première fois
                //executer l'action
                doAction(state->first, collisions,playerView);
                if(!firstStateActivated)
                    animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
            }

            //on est passé dans un état
            firstStateActivated=1;
        }
    }
}

void PlayerView::doAction(PlayerStateEnum state, std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView){
    CoupleFloat vectorDirection;
    Position newPosition;
    std::vector<std::vector<int>> collisionPlayer;
    switch(state){
    case dead:
        break;
    case standby:
        break;
    case defending:
        player.setState(defending,true);
        break;
    case receiveDamage:
        break;
    case attacking:
        std::cout<<" Attacking "<<std::endl;
        //on calcule les collisions entre players
        collisionPlayer = directionCollisionPlayers(*this, playerView);
        //on vérifie qu'il y a collision et que
        if(collisionPlayer.size() > 0 && collisionPlayer[0][0] > 0){
            for(auto i : collisionPlayer){
                if((i[0] == 3 && !looksRight) || (i[0] == 4 && looksRight)) {
                    attack(playerView, true);
                }
            }
        }
        break;
    case jumping :
        //std::cout<<" Jumping"<<std::endl;
        movePlayer(collisions, state);
        break;
    case movingLeft:
        //std::cout<<" Left"<<std::endl;
        movePlayer(collisions,state);
        break;
    case movingRight:
        //std::cout<<" Rigth"<<std::endl;
        movePlayer(collisions,state);
        break;
    case momentum :
        //std::cout<<" Momentum"<<std::endl;
        movePlayer(collisions,state);
        break;
    case idle:
        //std::cout<<" idle "<<std::endl;
        break;
    }
}

