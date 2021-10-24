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

sf::Sprite PlatformView::getSprite() const {
    return sprite;
}

Platform PlatformView::getPlatform() const {
    return platform;
}

void PlatformView::setSprite(sf::Sprite sprite) {
    this->sprite = sprite;
}

void PlatformView::setPlatform(Platform platform) {
    this->platform = platform;
}
