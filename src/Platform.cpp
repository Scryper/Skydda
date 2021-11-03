#include "Platform.h"

Platform::Platform() {
   Position defaultPlatform;
   this->position = defaultPlatform;

   Size defaultSize;
   this->size_ = defaultSize;
}

Platform::Platform(const Position position, const Size size_) {
    this->position = position;
    this->size_ = size_;
}

Platform::~Platform() { }

Platform::Platform(const Platform& other) {
    this->position=other.position;
    this->size_=other.size_;
}

Position Platform::getPosition() const{
    return position;
}

Size Platform::getSize() const{
    return size_;
}

void Platform::setPosition(Position position){
    this->position = position;
}

void Platform::setSize(Size size_){
    this->size_ = size_;
}
