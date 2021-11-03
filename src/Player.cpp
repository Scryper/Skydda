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

Player::Player(std::string name, double attack, bool defense, double health, Position position, Movement movement) {
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

Position Player::updatePosition(Position position, CoupleFloat direction, int collision) {
    return movement.updatePosition(position, direction, collision);
}

void Player::stopX(){
    this->movement.stopX();
}

void Player::stopY(){
    this->movement.stopY();
}
