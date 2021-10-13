#ifndef PLATFORMVIEW_H
#define PLATFORMVIEW_H

#include <SFML/Graphics.hpp>
#include "Platform.h"

class PlatformView {
    private:
        sf::Sprite sprite;
        Platform platform;

    public:
        PlatformView();
        PlatformView(sf::Sprite sprite_, Platform platform_);
        PlatformView(const PlatformView& other);
        virtual ~PlatformView();

        sf::Sprite getSprite() const;
        Platform getPlatform() const;

        void setSprite(sf::Sprite sprite);
        void setPlatform(Platform platform);
};

#endif // PLATFORMVIEW_H
