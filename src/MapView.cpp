#include "MapView.h"

MapView::MapView() {
}

/// !!! textures -> 0 : ground, 1 : long, 2 : small, 3 : tiny
MapView::MapView(Map mapModel, std::vector<sf::Texture*> textures) {
    this->mapModel = mapModel;
    this->textures = textures;
    selectMap(mapModel.getMapSeed());
}

MapView::~MapView() { }

std::vector<PlatformView> MapView::getBorders() const {
    return borders;
}

std::vector<PlatformView> MapView::getPlatforms() const {
    return platforms;
}

std::vector<PlatformView> MapView::getAllCollisions() const {
    std::vector<PlatformView> temp = platforms;
    for(PlatformView border : borders){
        temp.push_back(border);
    }
    return temp;
}

void MapView::drawPlatforms(sf::RenderWindow app) {
    for(PlatformView platformView : platforms) {
        app.draw(platformView.getSprite());
    }
}

void MapView::selectMap(int seed){
    if(seed == 1) {
        borders = createBorders(textures[0]);

        Position firstPosition(950, 1050);
        PlatformView firstPlatform = createPlatform(1.1f, .5f, firstPosition, textures[0]);

        Position secondPosition(900, 200);
        PlatformView secondPlatform = createPlatform(1.f, 1.f, secondPosition, textures[1]);

        Position thirdPosition(1400, 700);
        PlatformView thirdPlatform = createPlatform(1.f, 1.f, thirdPosition, textures[2]);

        Position fourthPosition(1800, 500);
        PlatformView fourthPlatform = createPlatform(1.f, 1.f, fourthPosition, textures[3]);

        platforms.push_back(firstPlatform);
        platforms.push_back(secondPlatform);
        platforms.push_back(thirdPlatform);
        platforms.push_back(fourthPlatform);
    }
    if(seed == 2) {
        borders = createBorders(textures[0]);

        Position firstPosition(950, 1050);
        PlatformView firstPlatform = createPlatform(1.1f, .5f, firstPosition, textures[0]);

        Position secondPosition(400, 700);
        PlatformView secondPlatform = createPlatform(1.f, 1.f, secondPosition, textures[2]);

        Position thirdPosition(1400, 700);
        PlatformView thirdPlatform = createPlatform(1.f, 1.f, thirdPosition, textures[2]);

        platforms.push_back(firstPlatform);
        platforms.push_back(secondPlatform);
        platforms.push_back(thirdPlatform);
    }
}
