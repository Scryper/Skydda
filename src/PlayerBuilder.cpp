#include "PlayerBuilder.h"

// The player is created automatically when we call the builder's constructor
PlayerBuilder::PlayerBuilder() {
    this->reset(); 
}

PlayerBuilder::~PlayerBuilder() { }

// sets or resets the player with the basic values (see default constructor of Player.cpp)
PlayerBuilder* PlayerBuilder::reset() {
    this->player = Player();
    return this; // allows to chain the methods
}

// This method is called at the end of the chain when the user has created the wanted player
Player PlayerBuilder::build() {
    return this->player;
}

// sets the name of the player
PlayerBuilder* PlayerBuilder::withName(std::string name) {
    this->player.setName(name);
    return this;
}

// sets the attack of the player
PlayerBuilder* PlayerBuilder::withAttack(float attack) {
    this->player.setAttack(attack);
    return this;
}

// sets the health of the player
PlayerBuilder* PlayerBuilder::withHealth(float health) {
    this->player.setHealth(health);
    return this;
}

// sets the position of the player
PlayerBuilder* PlayerBuilder::withPosition(Position position) {
    this->player.setPosition(position);
    return this;
}

// sets the movement of the player
PlayerBuilder* PlayerBuilder::withMovement(Movement movement) {
    this->player.setMovement(movement);
    return this;
}

// sets the points of the player
PlayerBuilder* PlayerBuilder::withPoints(int points) {
    this->player.setPoints(points);
    return this;
}
