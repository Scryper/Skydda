#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position::Position(const Position& other) {
    this->x = other.x;
    this->y = other.y;
}

Position::~Position() { }

Position& Position::operator=(const Position& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

///Getter
int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

///Setter
void Position::setX(int x){
    this->x = x;
}

void Position::setY(int y){
    this->y = y;
}
