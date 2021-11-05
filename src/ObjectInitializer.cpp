#include "ObjectInitializer.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, std::string pathToPlatform, Position platformPosition, sf::Texture *platformTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite platformSprite = initSprite(sizeOfSprite, pathToPlatform, platformPosition, platformTexture);

    Position viewPosition(platformPosition.getY(), platformPosition.getY() + 350);
    Platform platform(viewPosition, sizeOfSprite);
    PlatformView platformView(platformSprite, platform);

    return platformView;
}

//creates the border
std::vector<PlatformView> createBorder(std::string pathToPlatform, sf::Texture *platformTexture){
    Position topPosition(960, -35);
    PlatformView topPlatform = createPlatform(2.3f, .3f, "resources/images/platform/platform_default.png", topPosition, platformTexture);

    Position leftPosition(-40, 540);
    PlatformView leftPlatform = createPlatform(.1f, 4.5f, "resources/images/platform/platform_default.png", leftPosition, platformTexture);

    Position rigthPosition(1960, 540);
    PlatformView rigthPlatform = createPlatform(.1f, 4.5f, "resources/images/platform/platform_default.png", rigthPosition, platformTexture);

    std::vector<PlatformView> platformViews;
    platformViews.push_back(topPlatform);
    platformViews.push_back(leftPlatform);
    platformViews.push_back(rigthPlatform);

    return platformViews;
}

//creates the player
PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture,
                        sf::Keyboard::Key up,
                        sf::Keyboard::Key left,
                        sf::Keyboard::Key right,
                        sf::Keyboard::Key attack,
                        sf::Keyboard::Key protect,
                        bool looksRight,
                        std::string namePlayerStr) {
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.8f, 1.f);
    CoupleFloat maxSpeed(14.f, 20.f);
    float jumpHeight = 25.f;
    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite playerSprite = initSprite(sizeCouple, pathToPlayer, playerPosition, playerTexture);

    Player player(namePlayerStr, 10, false, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player,up,left,right,attack, protect,looksRight, sizeCouple);
    return playerView;
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
