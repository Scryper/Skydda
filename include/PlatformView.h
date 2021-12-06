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
        PlatformView(sf::Sprite sprite, Platform platform);
        PlatformView(const PlatformView& other);
        virtual ~PlatformView();
        PlatformView& operator=(const PlatformView& other);


        sf::Sprite getSprite() const;
        Platform getPlatform() const;

        void setSprite(sf::Sprite sprite);
        void setPlatform(Platform platform);
};

#endif // PLATFORMVIEW_H
