#include "Player.h"

Player::Player() {
    this->name = "Inconnu";
    this->attack = 0.0;
    this->defense = false;
    this->health = 0.0;
    Position p;
    Movement m;
    this->position = p;
    this->movement = m;
}

Player::Player(string name, double attack, bool defense, double health, Position position, Movement movement) {
    this->name = name;
    this->attack = attack;
    this->defense = defense;
    this->health = health;
    this->position = position;
    this->movement = movement;
}

Player::~Player() {
    //dtor
}

