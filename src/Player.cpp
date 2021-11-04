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
}

Player::Player(std::string name, float attack, bool defense, float health, Position position, Movement movement) {
    this->name = name;
    this->attack = attack;
    this->defense = defense;
    this->health = health;
    this->position = position;
    this->movement = movement;
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->attack = other.attack;
    this->defense = other.defense;
    this->health = other.health;
    this->position = other.position;
    this->movement = other.movement;
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

void Player::setHealth(float health) {
    this->health = health;
}

string Player::getName()const {
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

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<std::vector<int>> collisions) {
    return movement.updatePosition(position, direction, collisions);
}

void Player::stopX(){
    this->movement.stopX();
}

void Player::stopY(){
    this->movement.stopY();
}
