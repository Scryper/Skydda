#include "ObjectInitializer.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, Position platformPosition, sf::Texture *platformTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    CoupleFloat sizeOfSprite(sizeCouple);

    sf::Sprite platformSprite = initSprite(sizeOfSprite, platformPosition, platformTexture);

    Position viewPosition(platformPosition.getY(), platformPosition.getY() + 350);
    Platform platform(viewPosition, sizeOfSprite);
    PlatformView platformView(platformSprite, platform);

    return platformView;
}

//creates the border
std::vector<PlatformView> createBorders(sf::Texture *platformTexture){
    Position topPosition(960, -80);
    PlatformView topPlatform = createPlatform(2.3f, .3f, topPosition, platformTexture);

    Position leftPosition(-40, 540);
    PlatformView leftPlatform = createPlatform(.1f, 4.5f, leftPosition, platformTexture);

    Position rigthPosition(1960, 540);
    PlatformView rigthPlatform = createPlatform(.1f, 4.5f, rigthPosition, platformTexture);

    std::vector<PlatformView> platformViews;
    platformViews.push_back(topPlatform);
    platformViews.push_back(leftPlatform);
    platformViews.push_back(rigthPlatform);

    return platformViews;
}

//Creates the healthBar
HealthBarView createHealthBar(Player player, Position posHealthBar) {
    sf::RectangleShape healthBarIn;
    sf::RectangleShape healthBarOut;

    HealthBar healthBar(player.getHealth(), posHealthBar);
    HealthBarView healthBarView(&healthBar, healthBarIn, healthBarOut);

    healthBarView.setPositionHealthBarIn();
    healthBarView.setPositionHealthBarOut();

    healthBarView.actualiseColorHealthBarIn();
    healthBarView.actualiseColorHealthBarOut();

    healthBarView.actualiseSizeHealthBarIn(player.getHealth());
    healthBarView.actualiseSizeHealthBarOut();

    return healthBarView;
}
