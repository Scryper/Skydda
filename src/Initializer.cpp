#include "Initializer.h"

sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);
    sf::Sprite sprite = loadTexture(pathToSprite, sizeOfSprite, spritePosition, *spriteTexture);
    return sprite;
}

sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite = loadTexture(pathToSprite, sizeOfSprite, spritePosition, *spriteTexture);
    return sprite;
}

PlatformView createPlatform(float sizeX, float sizeY, std::string pathToPlatform, Position platformPosition, sf::Texture *platformTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite platformSprite = initSprite(sizeOfSprite, pathToPlatform, platformPosition, platformTexture);

    Position viewPosition(platformPosition.getY(), platformPosition.getY() + 350);
    Platform platform(viewPosition, sizeOfSprite);
    PlatformView platformView(platformSprite, platform);

    return platformView;
}

PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture) {
    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.5f, .5f);
    CoupleFloat maxSpeed(10.f, 10.f);
    Movement movement(velocity, acceleration, maxSpeed);

    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite playerSprite = initSprite(sizeCouple, pathToPlayer, playerPosition, playerTexture);

    Player player("Scryper", 100, true, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player);

    return playerView;
}
