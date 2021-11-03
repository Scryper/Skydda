#include "MapView.h"

MapView::MapView(int seed,sf::Texture *platformTexture)
{
    if(seed==1){
        border=createBorder("",platformTexture);
        Position p1(900,1000);
        PlatformView plat1 = createPlatform(5.5f, .3f, "", p1, platformTexture);
        Position p2(900, 200);
        PlatformView plat2 = createPlatform(1.f, .3f, "", p2, platformTexture);
        Position p3(1400, 700);
        PlatformView plat3 = createPlatform(.3f, .3f, "", p3, platformTexture);
        Position p4(1800, 500);
        PlatformView plat4 = createPlatform(.2f, .3f, "", p4, platformTexture);
        platforms.push_back(plat1);
        platforms.push_back(plat2);
        platforms.push_back(plat3);
        platforms.push_back(plat4);
    }
    if(seed==2){
      border=createBorder("",platformTexture);
        Position p1(900,1000);
        PlatformView plat1 = createPlatform(5.5f, .3f, "", p1, platformTexture);
        Position p2(400, 700);
        PlatformView plat2 = createPlatform(.3f, .3f, "", p2, platformTexture);
        Position p3(1400, 700);
        PlatformView plat3 = createPlatform(.3f, .3f, "", p3, platformTexture);
        platforms.push_back(plat1);
        platforms.push_back(plat2);
        platforms.push_back(plat3);
    }
}


MapView::~MapView()
{

}

std::vector<PlatformView> MapView::getBorders()const{
    return border;
}

std::vector<PlatformView> MapView::getPlatforms()const{
    return platforms;
}

std::vector<PlatformView> MapView::getAllCollisions()const{
    std::vector<PlatformView> temp = platforms;
    for(auto i : border){
        temp.push_back(i);
    }
    return temp;
}

void MapView::drawPlatforms(sf::RenderWindow app){
    for(auto i : platforms){
        app.draw(i.getSprite());
    }
}
