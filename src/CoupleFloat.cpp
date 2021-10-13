#include "CoupleFloat.h"

CoupleFloat::CoupleFloat(float x, float y):x(x),y(y) {

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
