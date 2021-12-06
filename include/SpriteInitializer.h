#ifndef SPRITEINITIALIZER_H
#define SPRITEINITIALIZER_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "CoupleFloat.h"
#include "TextureLoader.h"
#include "PlayerSprite.h"

sf::Sprite setSpriteOptions(sf::Sprite *sprite, CoupleFloat size_, Position position);

PlayerSprite setSpriteOptionsPlayer(sf::Sprite *sprite, CoupleFloat size_, CoupleFloat centerOfSprite, Position position);

///Initialize the sprite

///With a CoupleFloat
//return a Sprite object
sf::Sprite initSprite(CoupleFloat sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

//return a PlayerSprite object to add an hitbox to the sprite.
PlayerSprite initSpritePlayer(CoupleFloat sizeOfSprite, CoupleFloat centerOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

///With the coordinates
// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

///Without the sprite path but with CoupleFloat
// Initialize a sprite which has a texture already loaded
sf::Sprite initSprite(CoupleFloat sizeOfSprite, Position spritePosition, sf::Texture *spriteTexture);

///Without the sprite path and without CoupleFloat
// Initialize a sprite which has a texture already loaded
sf::Sprite initSprite(float sizeX, float sizeY, Position spritePosition, sf::Texture *spriteTexture);

#endif // SPRITEINITIALIZER_H
