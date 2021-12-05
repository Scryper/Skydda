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

Player& PlayerView::getPlayer() {
    return player;
}

PlayerSprite PlayerView::getSprite() const {
    return sprite;
}

// send state depending on the key
std::vector<PlayerStateEnum> PlayerView::getStatesFromInput(){
    inputPlayer();
    std::vector<PlayerStateEnum> tmp;
    // browse paler's keys
    for(auto i : keysPressed){
        tmp.push_back(i.first);
    }
    return tmp;
}

void PlayerView::getHit(int value) {
    player.getHit(value);
}

bool PlayerView::isLooksRigth() const {
    return looksRight;
}

void PlayerView::setLooksRigth(bool right){
    this->looksRight = right;
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
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

void PlayerView::flipSprite() {
    // We get the left of the hitbox
    float previousLeft = sprite.getGlobalHitbox().left;

    sprite.scale(-1.f, 1.f); // flip the sprite

    // we get the left of the flipped hitbox
    float presentLeft = sprite.getGlobalHitbox().left;

    // compute difference
    float diff = previousLeft-presentLeft;

    // move the player by the difference
    Position p(player.getPosition().getX() + diff, player.getPosition().getY());
    sprite.setPosition(p.getX(), p.getY());
    player.setPosition(p);
}

Position PlayerView::computeNewPosition(CoupleFloat vectorDirection, std::vector<CollisionVector> collisions){
    return player.updatePosition(player.getPosition(), vectorDirection, collisions);
}

void PlayerView::movePlayer(std::vector<CollisionVector> collisions, PlayerStateEnum state) {
    CoupleFloat vectorDirection = computeCoupleMovement();
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.getX() < 0)
       || (!looksRight && vectorDirection.getX() > 0)) {
        flipSprite();
        looksRight = !looksRight; // to know where he is looking
    }
    if(state == momentum){
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

void PlayerView::attack(PlayerView &playerAttacked, bool left, float factor){
    player.attackPlayer(playerAttacked.getPlayer(),this->clock.getElapsedTime().asMilliseconds(), factor, this->looksRight,playerAttacked.looksRight);
    this->soundManager->playRandomHittingSound();

    // if attacked -> change state
    if(playerAttacked.getPlayer().getHealth() != 0.f) {
        playerAttacked.getPlayer().setState(receiveDamage,true);
        // give a spedd with the hit's direction
        if(left)
        playerAttacked.getHit(10.f * factor * 0.8f);
        else
        playerAttacked.getHit(-10.f * factor * 0.8f);
    }
    else {
        this->soundManager->playDeathSound();
        playerAttacked.getPlayer().setState(dead,true);
    }
}

void PlayerView::animate(bool first,PlayerStateEnum state, bool boucle){
    if (first)
    animation.startAnimation(&this->sprite, state, boucle);
}

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

void PlayerView::computeFrame(std::vector<CollisionVector> collisions, PlayerView &playerView){
    //compute states
    std::vector<PlayerStateEnum> statesFromInput = getStatesFromInput();
    PlayerStateBoolArray playerStates =player.computeStates(statesFromInput, isBottomCollision(collisions));

    // if it was the first state -> if we have to do animation
    bool firstStateActivated = 0 ;

    // all non activated states' clocks to 0
    for (auto state : playerStates){
        if(state->second == 0){
            (*animation.getStateClock())[state->first]->second->restart();
        }
    }
    // browse states
    for (auto state : playerStates){
        // if state is activated
        if(state->second == 1) {
            //state timed?
            bool isTimed = constPlayerStates[state->first].isTimed;
            //state timed
            if(isTimed == 1 ) {
                // get state's clock
                sf::Clock* stateClock = (*animation.getStateClock())[state->first]->second;
                int timeElapsed = stateClock->getElapsedTime().asMilliseconds();
                int timeAction = constPlayerStates[state->first].timeAction;

                // verifiy the action's timing, if 0 -> do now
                bool actionImmediate = (timeAction == 0);
                if(actionImmediate == 1) {
                    doAction(state->first, collisions, playerView, true);
                }
                // action a t > 0
                else {
                    if(timeElapsed >= timeAction && timeElapsed <= timeAction + 16) {
                        doAction(state->first, collisions,playerView, true);
                    }
                    else {
                        doAction(state->first, collisions,playerView, false);
                    }
                }

                if(timeElapsed < 15){
                    animation.resetTour(state->first);
                }

                // if elapsed time is too big
                if(timeElapsed >= constPlayerStates[state->first].animationDuration) {
                    state->second = 0;
                    stateClock->restart();
                    animation.resetTour(state->first);
                }
                else {
                    if(!firstStateActivated)
                        animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
                }
            }
            // state not timed
            else{
                // if executed for the first time -> do action
                doAction(state->first, collisions,playerView,true);
                if(!firstStateActivated)
                    animate(!firstStateActivated,state->first,constPlayerStates[state->first].isPlayedOneTime);
            }
            // went through a state
            firstStateActivated = 1;
        }
    }
}

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
            // compute collisions between players
            collisionPlayer = directionCollisionPlayers(*this, playerView);
            // verify there is collision
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
            // compute collisions between players
            collisionPlayer = directionCollisionPlayers(*this, playerView);
            // verify there is collision
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
