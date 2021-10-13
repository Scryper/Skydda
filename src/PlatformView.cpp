#include "PlatformView.h"

PlatformView::PlatformView() { }

PlatformView::PlatformView(sf::Sprite sprite_, Platform platform_)
    : sprite(sprite_), platform(platform_) { }

PlatformView::PlatformView(const PlatformView& other)
    : sprite(other.sprite), platform(other.platform) { }

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
