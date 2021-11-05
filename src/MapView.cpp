#include "MapView.h"

MapView::MapView(int seed, sf::Texture *platformTexture, string path) {
    if(seed == 1) {
        border = createBorder(path, platformTexture);

        Position firstPosition(900, 1000);
        PlatformView firstPlatform = createPlatform(5.5f, .3f, path, firstPosition, platformTexture);

        Position secondPosition(900, 200);
        PlatformView secondPlatform = createPlatform(1.f, .3f, path, secondPosition, platformTexture);

        Position thirdPosition(1400, 700);
        PlatformView thirdPlatform = createPlatform(.3f, .3f, path, thirdPosition, platformTexture);

        Position fourthPosition(1800, 500);
        PlatformView fourthPlatform = createPlatform(.2f, .3f, path, fourthPosition, platformTexture);

        platforms.push_back(firstPlatform);
        platforms.push_back(secondPlatform);
        platforms.push_back(thirdPlatform);
        platforms.push_back(fourthPlatform);
    }
    if(seed == 2) {
        border = createBorder(path, platformTexture);

        Position firstPosition(900,1000);
        PlatformView firstPlatform = createPlatform(5.5f, .3f, path, firstPosition, platformTexture);

        Position secondPosition(400, 700);
        PlatformView secondPlatform = createPlatform(.3f, .3f, path, secondPosition, platformTexture);

        Position thirdPosition(1400, 700);
        PlatformView thirdPlatform = createPlatform(.3f, .3f, path, thirdPosition, platformTexture);

        platforms.push_back(firstPlatform);
        platforms.push_back(secondPlatform);
        platforms.push_back(thirdPlatform);
    }
}


MapView::~MapView() { }

std::vector<PlatformView> MapView::getBorders() const {
    return border;
}

std::vector<PlatformView> MapView::getPlatforms() const {
    return platforms;
}

std::vector<PlatformView> MapView::getAllCollisions() const {
    std::vector<PlatformView> temp = platforms;
    for(auto i : border){
        temp.push_back(i);
    }
    return temp;
}

void MapView::drawPlatforms(sf::RenderWindow app) {
    for(auto i : platforms){
        app.draw(i.getSprite());
    }
}
