#include "Player.h"

Player::Player() {
    this->name = "Inconnu";
    this->attack = 0.0;
    this->health = 0.0;
    Position defaultPosition = Position();
    Movement defaultMovement;
    this->position = defaultPosition;
    this->movement = defaultMovement;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    std::vector<bool> temp;
    for(int i = 0 ; i < 7;i++){
        temp.push_back(false);
    }
    this->state=temp;
    state[0]=true;
    state[6]=true;
}

Player::Player(std::string name, float attack, float health, Position position, Movement movement) {
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->position = position;
    this->movement = movement;
    timeLastAttack = 0;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;

    std::vector<bool> temp;
    for(int i = 0 ; i<7;i++){
        temp.push_back(false);
    }
    this->state=temp;
    state[0]=true;
    state[6]=true;
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->attack = other.attack;
    this->state = other.state;
    this->health = other.health;
    this->position = other.position;
    this->movement = other.movement;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
}

Player::~Player() { }

Movement Player::getMovement() const {
    return movement;
}

Position Player::getPosition() const {
    return position;
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

void Player::setDefense(bool def) {
    this->state[1] = def;
}

void Player::attackPlayer(Player &player, float clock) {
    //vérif que le player ne bloque pas l'attaque
    if(player.getDefense() == true){
        timeLastAttack = clock;
        return;
    }

    // verifiy that player's health > 0
    if(player.getHealth() <= 0){
        timeLastAttack = clock;
        return;
    }

    //fa attack animation
    if(clock - timeLastAttack >= durationBetweenAttacks){
        // deal damages
        double health = player.getHealth();
        if(health - attack > 0) {
            player.setHealth(health - attack);
        }
        else {
            player.setHealth(0.f);
        }
        timeLastAttack = clock;
    }
}

std::string Player::getName()const {
    return name;
}

float Player::getHealth()const {
    return health;
}

bool Player::getDefense()const{
    return state[1];
}

float Player::getAttack()const{
    return attack;
}

bool Player::isAlive()const {
    return state[0];
}

void Player::setAlive(bool alive){
    this->state[0] = alive;
}

std::vector<bool>& Player::getState(){
    return state;
}


Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<std::vector<std::vector<int>>> collisions, bool noTP) {
    return movement.updatePosition(position, direction, collisions, noTP);
}

void Player::stopX(){
    this->movement.stopX();
}

void Player::stopY(){
    this->movement.stopY();
}


