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

//creates the player
PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture) {
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.5f, 1.f);
    CoupleFloat maxSpeed(10.f, 20.f);
    Movement movement(velocity, acceleration, maxSpeed);

    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite playerSprite = initSprite(sizeCouple, pathToPlayer, playerPosition, playerTexture);

    Player player("Scryper", 100, true, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player);

    return playerView;
}