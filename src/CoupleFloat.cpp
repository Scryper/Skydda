#include "CoupleFloat.h"

CoupleFloat::CoupleFloat() {
    this->x = 0.;
    this->y = 0.;
}

CoupleFloat::CoupleFloat(float x_, float y_) {
    this->x = x_;
    this->y = y_;
}

CoupleFloat::CoupleFloat(const CoupleFloat& other):x(other.x),y(other.y) {

}

CoupleFloat::~CoupleFloat() {

}

float CoupleFloat::getX()const {
    return x;
}
float CoupleFloat::getY()const {
    return y;
}

void CoupleFloat::setX(float x) {
    this->x=x;
}
void CoupleFloat::setY(float y){
    this->y=y;
}
