#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder() {
    this->reset();
}

PlayerBuilder::~PlayerBuilder() { }

PlayerBuilder* PlayerBuilder::reset() {
    this->player = Player();
    return this;
}

Player PlayerBuilder::build() {
    return this->player;
}

PlayerBuilder* PlayerBuilder::withName(std::string name) {
    this->player.setName(name);
    return this;
}

PlayerBuilder* PlayerBuilder::withAttack(float attack) {
    this->player.setAttack(attack);
    return this;
}

PlayerBuilder* PlayerBuilder::withHealth(float health) {
    this->player.setHealth(health);
    return this;
}

PlayerBuilder* PlayerBuilder::withPosition(Position position) {
    this->player.setPosition(position);
    return this;
}

PlayerBuilder* PlayerBuilder::withMovement(Movement movement) {
    this->player.setMovement(movement);
    return this;
}

PlayerBuilder* PlayerBuilder::withPoints(int points) {
    this->player.setPoints(points);
    return this;
}
