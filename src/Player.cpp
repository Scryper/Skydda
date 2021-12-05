#include "Player.h"

Player::Player() {
    this->setName("Inconnu");
    this->setAttack(0.f);
    this->setHealth(0.f);
    Position defaultPosition = Position();
    Movement defaultMovement;
    this->setPosition(defaultPosition);
    this->setMovement(defaultMovement);
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();
}

Player::Player(std::string name, float attack, float health, Position position, Movement movement) {
    this->setName(name);
    this->setAttack(attack);
    this->setHealth(health);
    this->setPosition(position);
    this->setMovement(movement);
    timeLastAttack = 0;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();
}

Player::Player(const Player& other) {
    this->setName(other.name);
    this->setAttack(other.attack);
    this->setHealth(other.health);
    this->setPosition(other.position);
    this->setMovement(other.movement);
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();
}

Player::~Player() {
    //cout<<"destructeur player"<<endl;
    //stateDestroyer();
    //for (PlayerStatePair* p : state ){
        //delete p;
    //}
    state.clear();
}

void Player::setPosition(Position position) {
    this->position = position;
}

void Player::setPosition(float x, float y) {
    Position position(x,y);
    this->position = position;
}

void Player::setHealth(float health) {
    this->health = health;
}

void Player::setSpeedX(float x){
    CoupleFloat tmp (x,movement.getSpeed().getY());
    movement.setSpeed(tmp);
}

void Player::setAttack(float attack_){
    if(attack_ > MIN_ATTACK && attack_ < MAX_ATTACK) {
        this->attack = attack_;
    }
}

void Player::setName(std::string name_) {
    this->name = name_;
}

void Player::setMovement(Movement movement_) {
    this->movement = movement_;
}

bool Player::getState(PlayerStateEnum s)const{
    for(auto itStates : state){
        if(itStates->first==s){
            return itStates->second;
        }
     }
     return 0;
}

std::string Player::getName()const {
    return name;
}

float Player::getHealth()const {
    return health;
}

float Player::getAttack()const{
    return attack;
}

void Player::getHit(int value){
    movement.recul(value);
}

Movement Player::getMovement() const {
    return movement;
}

Position Player::getPosition() const {
    return position;
}

void Player::attackPlayer(Player &player, float clock, int factor, bool directionAttack, bool directionProtection) {
    // verifiy that player's health > 0
    if(player.getHealth() <= 0){
        timeLastAttack = clock;
        return;
    }

    //fa attack animation
    if(clock - timeLastAttack >= durationBetweenAttacks){
        // deal damages
        double health = player.getHealth();
        double damage = attack * factor;

        // evrifiy that the player isn't defendding himself
        if(player.getState(defending) == true && directionProtection !=directionAttack) damage/=4;

        if(health - damage > 0) {
            player.setHealth(health - damage);
        }
        else {
            player.setHealth(0.f);
        }
        timeLastAttack = clock;
    }
}

void Player::initStatePointer(PlayerStateEnum s, int val){
    PlayerStatePair *temp;
    temp = new PlayerStatePair{s, val};
    state.push_back(temp);
}

void Player::stateInitializer(){
    initStatePointer(dead, 0);
    initStatePointer(standby, 0);
    initStatePointer(defending, 0);
    initStatePointer(receiveDamage, 0);
    initStatePointer(specialAttacking, 0);
    initStatePointer(attacking, 0);
    initStatePointer(jumping, 0);
    initStatePointer(movingLeft, 0);
    initStatePointer(movingRight, 0);
    initStatePointer(momentum, 1);
    initStatePointer(idle, 0);
}

void Player::stateDestroyer(){
    //for()
    //state.clear();
}

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<CollisionVector> collisions) {
    return movement.updatePosition(position, direction, collisions);
}

void Player::setState(PlayerStateEnum s, bool value){
     for(auto itStates : state){
        if(itStates->first == s){
            itStates->second = value;
        }
     }
}

PlayerStateBoolArray Player::computeStates(std::vector<PlayerStateEnum> keyPressed, bool bottomCollision){
    // browse states in their order
    for(auto itStates : state) {
        // verifiy is state is activated
        if(itStates->second == 1) {
            // verify if the state isn't timed and that it depends on an user input
            if(constPlayerStates[itStates->first].isTimed == 0
               && constPlayerStates[itStates->first].onUserInput == 1) {
                // verifiy is the key isn't presseddoown, if yes, state = 1
                itStates->second = 0;
                if(isFoundInArray(keyPressed,itStates->first)) itStates->second = 1;
            }
            if(constPlayerStates[itStates->first].isTimed == 0
               && constPlayerStates[itStates->first].onUserInput == 0
               &&itStates->first == momentum) {
                itStates->second = 0;
               }
        }
        // state is not activated
        else{
             // verify that state depends on an user input
            if(constPlayerStates[itStates->first].onUserInput == 1) {
                // verifiy is the key isn't presseddoown, if yes, state = 1
                itStates->second = 0;
                if(isFoundInArray(keyPressed,itStates->first)) itStates->second = 1;
            }
        }
    }

    bool activated = 0;
    bool movementStateActivated = 0;

    // allows to know if it is a movement state or not
    // browse states in asce,ding order of states' importance
    for(auto itStates : state){
        if(activated == 1){
            itStates->second = 0;
        }
        // if state activated and not idle
        if(activated == 0 && itStates->second == 1 && itStates->first != idle){
            //état est activé
            activated = 1;
            // if movement state moevemtn state = true
            if(constPlayerStates[itStates->first].isMovement==1) movementStateActivated = true;
        }

    }
    // if there is no movement state AND horizontal and vertical speed != 0
    /// or there is no collision under the player and no movement
    if((movementStateActivated != 1
        && (movement.getSpeed().getX() != 0
        || movement.getSpeed().getY() != 0))
        || (!bottomCollision && movementStateActivated != 1)){
        state[momentum]->second = 1;
    }

    //si aucun état activated, on set le state a idle
    activated = 0;
    for (auto i : state){
        if(i->second == 1) activated = 1;
    }

    if(!activated) state[idle]->second = 1;

    return state;
}

template <typename T>
bool Player::isFoundInArray(std::vector<T> vect, T element){
    return std::find(vect.begin(), vect.end(), element) != vect.end();
}
