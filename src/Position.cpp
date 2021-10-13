#include "Position.h"

Position::Position(int x, int y):x(x),y(y) {

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

void Position::setX(int x_){
    this->x = x;
}
void Position::setY(int y_){
    this->y = y;
}
