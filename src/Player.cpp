#include "Player.h"

Player::Player() {
    this->name = "Inconnu";
    this->attack = 0.0;
    this->defense = false;
    this->health = 0.0;
    Position defaultPosition = Position();
    Movement defaultMovement;
    this->position = defaultPosition;
    this->movement = defaultMovement;
    alive = true;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
}

Player::Player(std::string name, float attack, bool defense, float health, Position position, Movement movement) {
    this->name = name;
    this->attack = attack;
    this->defense = defense;
    this->health = health;
    this->position = position;
    this->movement = movement;
    timeLastAttack = 0;
    alive = true;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->attack = other.attack;
    this->defense = other.defense;
    this->health = other.health;
    this->position = other.position;
    this->movement = other.movement;
    this->alive = other.alive;
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
    this->defense = def;
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
    return defense;
}

float Player::getAttack()const{
    return attack;
}

bool Player::isAlive()const {
    return alive;
}

void Player::setAlive(bool alive){
    this->alive = alive;
}

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<std::vector<std::vector<int>>> collisions) {
    return movement.updatePosition(position, direction, collisions);
}

void Player::stopX(){
    this->movement.stopX();
}

void Player::stopY(){
    this->movement.stopY();
}


