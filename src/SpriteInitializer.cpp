#include "SpriteInitializer.h"

sf::Sprite setSpriteOptions(sf::Sprite *sprite, Size size_, Position position) {
    sprite->setScale(size_.getFactor().getX(), size_.getFactor().getY());

    // set the origin of the image to its center
    sprite->setOrigin(sprite->getTexture()->getSize().x / 2, sprite->getTexture()->getSize().y / 2);
    sprite->setPosition(position.getX(), position.getY());

    return *sprite;
}

sf::Sprite setSpriteOptionsPlayer(sf::Sprite *sprite, Size size_, Size centerOfSprite, Position position) {
    sprite->setScale(size_.getFactor().getX(), size_.getFactor().getY());

    // set the origin of the image to its center
    sprite->setOrigin(centerOfSprite.getFactor().getX() / 2, centerOfSprite.getFactor().getY() / 2);
    sprite->setPosition(position.getX(), position.getY());

    return *sprite;
}
// Initialize the sprite with created sizeCouple
sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite = loadTexture(pathToSprite, *spriteTexture);
    sprite = setSpriteOptions(&sprite, sizeOfSprite, spritePosition);
    return sprite;
}

sf::Sprite initSpritePlayer(Size sizeOfSprite, Size centerOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite = loadTexture(pathToSprite, *spriteTexture);
    sprite = setSpriteOptionsPlayer(&sprite, sizeOfSprite, centerOfSprite, spritePosition);
    return sprite;
}

// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);
    sf::Sprite sprite = initSprite(sizeOfSprite, pathToSprite, spritePosition, spriteTexture);
    return sprite;
}

sf::Sprite initSprite(Size sizeOfSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite(*spriteTexture);
    sprite = setSpriteOptions(&sprite, sizeOfSprite, spritePosition);

    return sprite;
}

// Initialize a sprite which has a texture already loaded
sf::Sprite initSprite(float sizeX, float sizeY, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);
    sf::Sprite sprite = initSprite(sizeOfSprite, spritePosition, spriteTexture);
    return sprite;
}
