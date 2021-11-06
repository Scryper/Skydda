#ifndef SPRITEINITIALIZER_H
#define SPRITEINITIALIZER_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "Size.h"
#include "CoupleFloat.h"
#include "TextureLoader.h"

sf::Sprite setSpriteOptions(sf::Sprite *sprite, Size size_, Position position);

sf::Sprite setSpriteOptionsPlayer(sf::Sprite *sprite, Size size_, Size centerOfSprite, Position position);

// Initialize the sprite with created sizeCouple
sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

sf::Sprite initSpritePlayer(Size sizeOfSprite, Size centerOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

sf::Sprite initSprite(Size sizeOfSprite, Position spritePosition, sf::Texture *spriteTexture);

// Initialize a sprite which has a texture already loaded
sf::Sprite initSprite(float sizeX, float sizeY, Position spritePosition, sf::Texture *spriteTexture);

#endif // SPRITEINITIALIZER_H
