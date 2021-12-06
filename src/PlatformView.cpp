#include "PlatformView.h"

PlatformView::PlatformView() { }

PlatformView::PlatformView(sf::Sprite sprite, Platform platform) {
    this->sprite = sprite;
    this->platform = platform;
}

PlatformView::PlatformView(const PlatformView& other) {
    this->sprite = other.sprite;
    this->platform = other.platform;
}

PlatformView::~PlatformView() { }

PlatformView& PlatformView::operator=(const PlatformView& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->sprite = rhs.sprite;
    this->platform = rhs.platform;
    return *this;
}

///Getter
sf::Sprite PlatformView::getSprite() const {
    return sprite;
}

Platform PlatformView::getPlatform() const {
    return platform;
}

///Setter
void PlatformView::setSprite(sf::Sprite sprite) {
    this->sprite = sprite;
}

void PlatformView::setPlatform(Platform platform) {
    this->platform = platform;
}
