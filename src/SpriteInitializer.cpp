#include "SpriteInitializer.h"

sf::Sprite setSpriteOptions(sf::Sprite *sprite, CoupleFloat size_, Position position) {
    sprite->setScale(size_.getX(), size_.getY());

    // set the origin of the image to its center
    sprite->setOrigin(sprite->getTexture()->getSize().x / 2, sprite->getTexture()->getSize().y / 2);
    sprite->setPosition(position.getX(), position.getY());

    return *sprite;
}

PlayerSprite setSpriteOptionsPlayer(PlayerSprite *sprite, CoupleFloat size_, CoupleFloat centerOfSprite, Position position) {
    sprite->setScale(size_.getX(), size_.getY());

    // set the origin of the image to its center
    sprite->setOrigin(centerOfSprite.getX() / 2, centerOfSprite.getY() / 2);
    sprite->setPosition(position.getX(), position.getY());

    //create the hitbox and set the hitbox of the playerSprite
    sf::FloatRect hitbox(0, 50, 170, 273);
    sprite->setHitbox(hitbox);

    return *sprite;
}
// Initialize the sprite with created sizeCouple
sf::Sprite initSprite(CoupleFloat sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite = loadTexture(pathToSprite, *spriteTexture);
    sprite = setSpriteOptions(&sprite, sizeOfSprite, spritePosition);
    return sprite;
}

PlayerSprite initSpritePlayer(CoupleFloat sizeOfSprite, CoupleFloat centerOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    PlayerSprite sprite = loadTexturePlayer(pathToSprite, *spriteTexture);
    sprite = setSpriteOptionsPlayer(&sprite, sizeOfSprite, centerOfSprite, spritePosition);
    return sprite;
}

// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeOfSprite(sizeX, sizeY);
    sf::Sprite sprite = initSprite(sizeOfSprite, pathToSprite, spritePosition, spriteTexture);
    return sprite;
}

// Initialize a sprite which has a texture already loaded
sf::Sprite initSprite(CoupleFloat sizeOfSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite(*spriteTexture);
    sprite = setSpriteOptions(&sprite, sizeOfSprite, spritePosition);

    return sprite;
}

// Initialize a sprite which has a texture already loaded but without CoupleFloat
sf::Sprite initSprite(float sizeX, float sizeY, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeOfSprite(sizeX, sizeY);
    sf::Sprite sprite = initSprite(sizeOfSprite, spritePosition, spriteTexture);
    return sprite;
}
