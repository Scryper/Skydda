#include "PlayerView.h"
#include "Collision.h"
#include "Animation.h"

PlayerView::PlayerView() {
    PlayerSprite defaultSprite;
    this->setSprite(defaultSprite);
    Player defaultPlayer;
    this->setPlayer(defaultPlayer);
    Animation anim;
    this->animation = anim;
}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
    this->keys = other.keys;
    this->looksRight = other.looksRight;
    Animation anim;
    this->animation = anim;
}

PlayerView::~PlayerView() { }

PlayerView& PlayerView::operator=(const PlayerView& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->sprite = rhs.sprite;
    this->player = rhs.player;
    this->keys = rhs.keys;
    this->looksRight = rhs.looksRight;
    this->animation = rhs.animation;
    return *this;
}

Player& PlayerView::getPlayer() {
    return player;
}

PlayerSprite PlayerView::getSprite() const {
    return sprite;
}

bool PlayerView::isLooksRigth()const{
    return looksRight;
}

void PlayerView::setLooksRigth(bool right){
    this->looksRight = right;
}

void PlayerView::setSprite(PlayerSprite sprite_) {
    this->sprite = sprite_;
}

void PlayerView::setPlayer(Player player_) {
    this->player = player_;
}

void PlayerView::setKeys(std::vector<pair<PlayerStateEnum,sf::Keyboard::Key>> keys_) {
    this->keys = keys_;
}

//flip the sprite of the player, based on the hitbox and not the sprite
void PlayerView::flipSprite() {

    //on récupère la gauche de la hitbox actuelle;
    float previousLeft = sprite.getGlobalHitbox().left;

    //on retourne le sprite
    sprite.scale(-1.f, 1.f);

    //on récupère la gauche de la hitbox retournée
    float presentLeft = sprite.getGlobalHitbox().left;

    //on cacule la différence entre les deux
    float diff = previousLeft-presentLeft;

    //on déplace le perso de la différence
    Position p(player.getPosition().getX()+diff, player.getPosition().getY());
    sprite.setPosition(p.getX(), p.getY());
    player.setPosition(p);
}

//compute the new position of the player
Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<CollisionVector> collisions){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions);
}

//move the player
void PlayerView::movePlayer(std::vector<CollisionVector> collisions, PlayerStateEnum state) {
    CoupleFloat vectorDirection = computeCoupleMovement();

    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0) || (!looksRight && vectorDirection.getX() > 0)) {
        flipSprite();
        looksRight = !looksRight; // to know where he is looking
    }

    //if the state is momentum, the input should not impact the movement
    if(state==momentum){
        CoupleFloat tmp(0.f, 0.f);
        vectorDirection = tmp;
    }

    //compute the position and set it
    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());
}

//actualise the list of pressed keys
void PlayerView::inputPlayer(){
    std::vector<std::pair<PlayerStateEnum,sf::Keyboard::Key>> tmp;
    for (auto key : keys){
        if(sf::Keyboard::isKeyPressed(key.second))
            tmp.push_back(key);
    }
    keysPressed = tmp;
}

//send a vector of state possibles based on player's input
std::vector<PlayerStateEnum> PlayerView::getStatesFromInput(){
    inputPlayer();
    std::vector<PlayerStateEnum> tmp;
    for(auto i : keysPressed){
        tmp.push_back(i.first);
    }
    return tmp;
}

//compute the direction the movement should do based on the input (not on the state yet)
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
            couple.setX(couple.getX() + deltaTime);
        }
    }
    return couple;
}

void PlayerView::getHit(int value){
    player.getHit(value);
}

//attack a playerView
void PlayerView::attack(PlayerView &playerAttacked, bool left, float factor){
    //attack the player
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds(), factor, this->looksRight,playerAttacked.looksRight);

    //play the sound
    this->soundManager->playRandomHittingSound();

    //if the player is not dead -> knockback
    if(playerAttacked.getPlayer().getHealth() != 0.f){
        playerAttacked.getPlayer().setState(receiveDamage,true);
        //speed is in the direction of the attack
        if(left)
        playerAttacked.getHit(10.f * factor * 0.8f);
        else
        playerAttacked.getHit(-10.f * factor * 0.8f);
    }
    //if the player is dead
    else{
        this->soundManager->playDeathSound();
        playerAttacked.getPlayer().setState(dead,true);
    }
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

//animate the player based on his state
void PlayerView::animate(bool first,PlayerStateEnum state, bool boucle){
    //if this is the first state activated
    if (first)
    animation.startAnimation(&this->sprite, state, boucle);
}

//check if the player touches something below him
bool PlayerView::isBottomCollision(std::vector<CollisionVector> coll){
    for(auto collisions : coll){
        for(auto coteCollision : collisions){
            if(coteCollision.first==top){
                return true;
            }
        }
    }
    return false;
}

//compte the state, do the action and animate the playerview
void PlayerView::computeFrame(std::vector<CollisionVector> collisions, PlayerView &playerView){

    //compute states
    std::vector<PlayerStateEnum> statesFromInput = getStatesFromInput();
    PlayerStateBoolArray playerStates =player.computeStates(statesFromInput, isBottomCollision(collisions));

    //if it is the first state activated (if the animation should be displayed
    bool firstStateActivated = 0 ;

    //all non activated state clock -> restarted
    for (auto state : playerStates){
        if(state->second==0){
            (*animation.getStateClock())[state->first]->second->restart();
        }
    }

    for (auto state : playerStates){
        //state activated?
        if(state->second==1){

            //state is timed?
            bool isTimed = constPlayerStates[state->first].isTimed;
            //if timed
            if(isTimed == 1 ){

                //get the clock of the state
                sf::Clock* stateClock = (*animation.getStateClock())[state->first]->second;
                int timeElapsed = stateClock->getElapsedTime().asMilliseconds();
                int timeAction = constPlayerStates[state->first].timeAction;

                //check the timming of the action, if = 0, action must happen immediately
                bool actionImmediate = (timeAction==0);
                if(actionImmediate == 1){
                    doAction(state->first, collisions,playerView,true);
                }
                //timming of the action > 0
                else{
                    //if time is bewteen the timming of the action
                    if(timeElapsed>=timeAction&& timeElapsed<=timeAction+16){
                        doAction(state->first, collisions,playerView, true);
                    }
                    //else don't do the action
                    else{
                        doAction(state->first, collisions,playerView, false);
                    }
                }
                //if it's the first time the anim is played
                if(timeElapsed<15){
                    animation.resetTour(state->first);
                }

                //if the time elapsed is exceed the max time of the anim
                if(timeElapsed>=constPlayerStates[state->first].animationDuration){
                    state->second = 0;
                    stateClock->restart();
                    animation.resetTour(state->first);
                }
                else{
                    //if it is not the first state, do the action still
                    if(!firstStateActivated)
                        animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
                }


            }
            //state not timed
            else{
                //do the action
                doAction(state->first, collisions,playerView,true);
                //if it is the first state activated do the animation
                if(!firstStateActivated)
                    animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
            }

            //it is not the first state activated anymore
            firstStateActivated=1;
        }
    }
}

//do an action based on state
void PlayerView::doAction(PlayerStateEnum state, std::vector<CollisionVector> collisions, PlayerView &playerView, bool doActionNow){
    CoupleFloat vectorDirection;
    Position newPosition;
    CollisionVector collisionPlayer;
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
    case specialAttacking:
        if(doActionNow){
            //compute collisions between players
            collisionPlayer = directionCollisionPlayers(*this, playerView);
            //check if there is a collision
            if(collisionPlayer.size() > 0 && collisionPlayer[0].first < 5){
                for(auto i : collisionPlayer){
                    if((i.first == rigthCol && !looksRight) || (i.first == leftCol && looksRight)) {
                        bool direction = !(i.first == rigthCol && !looksRight);
                        attack(playerView, direction,2.5);
                    }
                }
            }
        }

        break;
    case attacking:
        if(doActionNow){
            //compute collisions between players
            collisionPlayer = directionCollisionPlayers(*this, playerView);
           //check if there is a collision
            if(collisionPlayer.size() > 0 && collisionPlayer[0].first < 5){
                for(auto i : collisionPlayer){
                    if((i.first == rigthCol && !looksRight) || (i.first == leftCol && looksRight)) {
                        bool direction = !(i.first == rigthCol && !looksRight);
                        attack(playerView, direction,1);
                    }
                }
            }
        }
        movePlayer(collisions, state);
        break;
    case jumping :
        movePlayer(collisions, state);
        break;
    case movingLeft:
        movePlayer(collisions,state);
        break;
    case movingRight:
        movePlayer(collisions,state);
        break;
    case momentum :
        movePlayer(collisions,state);
        break;
    case idle:
        break;
    }
}

