#include "SpriteInitializer.h"

// Initialize the sprite with created sizeCouple
sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    sf::Sprite sprite = loadTexture(pathToSprite, sizeOfSprite, spritePosition, *spriteTexture);
    return sprite;
}

// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);
    sf::Sprite sprite = initSprite(sizeOfSprite, pathToSprite, spritePosition, spriteTexture);
    return sprite;
}
