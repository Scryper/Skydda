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
    Position top(960, -35);
    PlatformView topP = createPlatform(2.3f, .3f, "resources/images/platform/platform_default.png", top, platformTexture);
    Position leftPosition(-40, 540);
    PlatformView leftP = createPlatform(.1f, 4.5f, "resources/images/platform/platform_default.png", leftPosition, platformTexture);
    Position rigthPosition(1960, 540);
    PlatformView rigthP = createPlatform(.1f, 4.5f, "resources/images/platform/platform_default.png", rigthPosition, platformTexture);

    std::vector<PlatformView> vect;
    vect.push_back(topP);
    vect.push_back(leftP);
    vect.push_back(rigthP);

    return vect;
}

//creates the player
PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture) {
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.5f, 1.f);
    CoupleFloat maxSpeed(10.f, 20.f);
    float jumpHeight = 25.f;
    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite playerSprite = initSprite(sizeCouple, pathToPlayer, playerPosition, playerTexture);

    Player player("Scryper", 100, true, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player);

    return playerView;
}
