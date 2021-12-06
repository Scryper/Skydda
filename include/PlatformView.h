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

        ///Getter
        sf::Sprite getSprite() const;
        Platform getPlatform() const;

        ///Setter
        void setSprite(sf::Sprite sprite);
        void setPlatform(Platform platform);
};

#endif // PLATFORMVIEW_H
