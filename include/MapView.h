#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>

#include<PlatformView.h>
#include<ObjectInitializer.h>

class MapView
{
    private:
        std::vector<PlatformView> platforms;
        std::vector<PlatformView> border;

    public:
        MapView(int seed, sf::Texture *platformTexture);
        virtual ~MapView();
        std::vector<PlatformView> getBorders()const;
        std::vector<PlatformView> getPlatforms()const;
        std::vector<PlatformView> getAllCollisions()const;
        void drawPlatforms(sf::RenderWindow app);
};

#endif // MAPVIEW_H
