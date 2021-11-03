#ifndef SPRITEINITIALIZER_H
#define SPRITEINITIALIZER_H

#include <SFML/Graphics.hpp>

#include "Position.h"
#include "Size.h"
#include "CoupleFloat.h"
#include "TextureLoader.h"

// Initialize the sprite with created sizeCouple
sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

// Initialize the sprite and creates itself the sizeCouple
sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);

#endif // SPRITEINITIALIZER_H
