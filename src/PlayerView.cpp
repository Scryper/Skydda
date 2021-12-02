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
           // state = 5;
            couple.setY(couple.getY() - deltaTime);
        }
        //left
        if(key.second == keys[1].second) {
            //state = 6;
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

void PlayerView::attack(PlayerView &playerAttacked){
    cout<<"ici"<<endl;
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds());

    //si attaqué changer state
    if(playerAttacked.getPlayer().getHealth() != 0.f){

    }
    else{

    }
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

void PlayerView::animate(bool first,PlayerStateEnum state, bool boucle){
    if (first)
    animation.startAnimation(&this->sprite, state, boucle);
}

void PlayerView::computeFrame(std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView){

    //compute collisions?

    //compute states
    std::vector<PlayerStateEnum> statesFromInput = getStatesFromInput();
    PlayerStateBoolArray playerStates =player.computeStates(statesFromInput);

    //for (auto i : )

    //pour se souvenir de si c'est le premier état
    bool firstStateActivated = 0 ;

    //On passe la clock de tous les états non activés a 0
    for (auto state : playerStates){
        if(state->second==0){
            for(auto timer : *animation.getStateClock()){
                //si c'est la clock associée au state
                if (timer->first == state->first){
                    timer->second->restart();
                }
            }
        }
    }
    //parcourir les états
    for (auto state : playerStates){
        //regarder si l'état est activé
        if(state->second==1){
            //état timed?
            bool isTimed = 0;
            //on parcour les constPlayerState pour savoir si l'état est timed
            for (auto constState : constPlayerStates){
                if(state->first== constState.state && constState.isTimed==1){
                    isTimed = 1;
                }
            }

            //si l'état est timed
            if(isTimed == 1 ){
                //on parcours les clock pour trouver celle correspondante
                for(auto timer : *animation.getStateClock()){
                    //si c'est la clock associée au state
                    if (timer->first == state->first){
                        //on regarde si on l'a pas dépassée
                        if(timer->second->getElapsedTime().asMilliseconds()>=constPlayerStates[state->first].animationDuration){
                            //si c'est le cas c'est qu'il faut remettre le state a 0
                            state->second = 0;
                            timer->second->restart();
                        }
                        else{
                            animate(!firstStateActivated,state->first, false);
                        }

                        //on vérif le timming de l'action, si c'est 0 il faut l'effectuer de suite
                        bool actionImmediate = 0;
                        for (auto constState : constPlayerStates){
                            if(state->first== constState.state && constState.timeAction==0){
                                actionImmediate = 1;
                            }
                        }
                        //action a t = 0
                        if(actionImmediate == 1){
                            doAction(state->first, collisions,playerView);
                        }
                        //action a t > 0
                        else{
                            //si le temps est compris entre la limite et limite + 15 faire l'action
                            for (auto constState : constPlayerStates){
                                if(state->first== constState.state &&
                                   (timer->second->getElapsedTime().asMilliseconds()>=constState.timeAction
                                    && timer->second->getElapsedTime().asMilliseconds()<=constState.timeAction+16)){
                                    actionImmediate = 1;
                                }
                            }
                        }
                    }
                }
            }
            else{
                //executer l'action
                doAction(state->first, collisions,playerView);
                animate(!firstStateActivated,state->first, false);
            }

            //on est passé dans un état
            firstStateActivated=1;
        }
    }
}

void PlayerView::doAction(PlayerStateEnum state, std::vector<std::vector<std::vector<int>>> collisions, PlayerView &playerView){
    CoupleFloat vectorDirection;
    Position newPosition;
    std::vector<std::vector<int>> collision;
    switch(state){
    case dead:
        std::cout<<" dead "<<std::endl;
        break;
    case standby:
        std::cout<<" standby "<<std::endl;
        break;
    case defending:
        std::cout<<" Defending "<<std::endl;
        player.setState(defending,true);
        break;
    case receiveDamage:
        std::cout<<" receiveDamage "<<std::endl;
        break;
    case attacking:
        std::cout<<" Attacking "<<std::endl;
        collision = directionCollisionPlayers(*this, playerView);
        if(collision.size() > 0 && collision[0][0] > 0){
            for(auto i : collision){
                if((i[0] == 3 && !looksRight) || (i[0] == 4 && looksRight)) {
                    attack(playerView);
                }
            }
        }
        break;
    case jumping :
        std::cout<<" Jumping"<<std::endl;
        movePlayer(collisions, state);
        break;
    case movingLeft:
        std::cout<<" Left"<<std::endl;
        movePlayer(collisions,state);
        break;
    case movingRight:
        std::cout<<" Rigth"<<std::endl;
        movePlayer(collisions,state);
        break;
    case momentum :
        std::cout<<" Momentum"<<std::endl;
        movePlayer(collisions,state);
        break;
    case idle:
        std::cout<<" idle "<<std::endl;
        break;
    }
}

