#include "MapView.h"

MapView::MapView() {}

/*Constructor of mapview*/
/// !!! textures -> 0 : ground, 1 : long, 2 : small, 3 : tiny, 4 : invisibleWall, 5 : wood
MapView::MapView(Map mapModel, std::vector<sf::Texture*> textures) {
    this->mapModel = mapModel;
    this->textures = textures;
    selectMap(mapModel.getMapSeed());
}

MapView::~MapView() { }

MapView::MapView(const MapView& other) {
    this->mapModel = other.mapModel;
    this->textures = other.textures;
    selectMap(mapModel.getMapSeed());
}

MapView& MapView::operator=(const MapView& rhs) {
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->mapModel = rhs.mapModel;
    this->textures = rhs.textures;
    selectMap(mapModel.getMapSeed());
    return *this;
}

std::vector<PlatformView> MapView::getBorders() const {
    return borders;
}

std::vector<PlatformView> MapView::getPlatforms() const {
    return platforms;
}

// In this method, we get all the borders of the screen
// there is platforms "outside" the screen, that the user don't see but allows the game
// to keep the players inside the map
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

// Each seed have platform at different positions
// so with the seed, we know what positions we need to put the platforms
void MapView::selectMap(int seed){
    if(seed == 1) {
        borders = createBorders(textures[4]); // create the borders

        Position platformGroundPosition(960, 1090); // set a position
        // apply the position and a texture on the platform
        PlatformView platformGround = createPlatform(0.218f, 0.20f, platformGroundPosition, textures[0]);

        Position platformWood1Position(800, 600);
        PlatformView platformWood1 = createPlatform(0.5f, 0.5f, platformWood1Position, textures[5]);

        Position platformWood2Position(1500, 600);
        PlatformView platformWood2 = createPlatform(0.5f, 0.5f, platformWood2Position, textures[5]);

        Position houseWallPosition(200, 892);
        PlatformView houseWall = createPlatform(1.f, 1.f, houseWallPosition, textures[6]);

        // push the platforms in the vector
        platforms.push_back(houseWall);
        platforms.push_back(platformGround);
        platforms.push_back(platformWood1);
        platforms.push_back(platformWood2);
    }
    if(seed == 2) {
        borders = createBorders(textures[4]);

        Position platformGroundPosition(960, 1090);
        PlatformView platformGround = createPlatform(0.218f, 0.20f, platformGroundPosition, textures[0]);

        Position platformWood1Position(1300, 240);
        PlatformView platformWood1 = createPlatform(0.8f, 0.5f, platformWood1Position, textures[5]);

        Position platformWood2Position(1000, 700);
        PlatformView platformWood2 = createPlatform(0.4f, 0.5f, platformWood2Position, textures[5]);

        Position platformWood3Position(400, 500);
        PlatformView platformWood3 = createPlatform(0.4f, 0.5f, platformWood3Position, textures[5]);

        Position houseWallPosition(1700, 892);
        PlatformView houseWall = createPlatform(1.f, 1.f, houseWallPosition, textures[6]);

        platforms.push_back(houseWall);
        platforms.push_back(platformGround);
        platforms.push_back(platformWood1);
        platforms.push_back(platformWood2);
        platforms.push_back(platformWood3);
    }
    if(seed == 3) {
        borders = createBorders(textures[4]);

        Position platformGroundPosition(960, 1090);
        PlatformView platformGround = createPlatform(0.218f, 0.20f, platformGroundPosition, textures[0]);

        Position platformWood1Position(1000, 600);
        PlatformView platformWood1 = createPlatform(1.2f, 0.5f, platformWood1Position, textures[5]);

        Position houseWall1Position(200, 892);
        PlatformView houseWall1 = createPlatform(1.f, 1.f, houseWall1Position, textures[6]);

        Position houseWall2Position(1715, 892);
        PlatformView houseWall2 = createPlatform(1.f, 1.f, houseWall2Position, textures[6]);

        platforms.push_back(houseWall1);
        platforms.push_back(houseWall2);
        platforms.push_back(platformGround);
        platforms.push_back(platformWood1);
    }
}
