#include "Position.h"

Position::Position(int x_, int y_):x(x_),y(y_) {

}

Position::Position(const Position& other): x(other.x), y(other.y) {

}

Position::~Position() {

}

int Position::getX()const {
    return x;
}
int Position::getY()const {
    return y;
}

void Position::setX(int x){
    this->x = x;
}

void Position::setY(int y){
    this->y = y;
}
