#include "CoupleFloat.h"

CoupleFloat::CoupleFloat() {
    this->x = 0.f;
    this->y = 0.f;
}

CoupleFloat::CoupleFloat(float x_, float y_) {
    this->x = x_;
    this->y = y_;
}

CoupleFloat::CoupleFloat(const CoupleFloat& other) {
    this->x = other.x;
    this->y = other.y;
}

CoupleFloat::~CoupleFloat() {

}

CoupleFloat& CoupleFloat::operator=(const CoupleFloat& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

float CoupleFloat::getX()const {
    return x;
}
float CoupleFloat::getY()const {
    return y;
}

void CoupleFloat::setX(float x) {
    this->x = x;
}
void CoupleFloat::setY(float y){
    this->y = y;
}
