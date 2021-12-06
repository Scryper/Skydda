#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <vector>

#include<PlatformView.h>
#include<ObjectInitializer.h>

#include "Map.h"

/*This map is what the user will see while playing*/
class MapView {
    private:
        Map mapModel;
        std::vector<PlatformView> platforms;
        std::vector<PlatformView> borders;
        std::vector<sf::Texture*> textures;

    public:
        MapView();
        MapView(Map mapModel, std::vector<sf::Texture*> textures);
        virtual ~MapView();
        MapView(const MapView& other);
        MapView& operator=(const MapView& other);


        std::vector<PlatformView> getBorders() const;
        std::vector<PlatformView> getPlatforms() const;
        std::vector<PlatformView> getAllCollisions() const;

        void drawPlatforms(sf::RenderWindow app);

        void selectMap(int seed);
};

#endif // MAPVIEW_H
