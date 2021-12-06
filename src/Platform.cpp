#include "Platform.h"

Platform::Platform() {
   Position defaultPlatform;
   this->position = defaultPlatform;

   CoupleFloat defaultSize;
   this->size_ = defaultSize;
}

Platform::Platform(const Position position, const CoupleFloat size_) {
    this->position = position;
    this->size_ = size_;
}

Platform::~Platform() { }

Platform::Platform(const Platform& other) {
    this->position=other.position;
    this->size_=other.size_;
}

Platform& Platform::operator=(const Platform& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->position = rhs.position;
    this->size_ = rhs.size_;
    return *this;
}

///Getter
Position Platform::getPosition() const {
    return position;
}

CoupleFloat Platform::getSize() const {
    return size_;
}

///Setter
void Platform::setPosition(Position position) {
    this->position = position;
}

void Platform::setSize(CoupleFloat size_) {
    this->size_ = size_;
}
