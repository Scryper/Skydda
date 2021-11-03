#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <SFML/Graphics.hpp>

#include "TextureLoader.h"
#include "Player.h"
#include "PlayerView.h"
#include "Platform.h"
#include "PlatformView.h"

sf::Sprite initSprite(float sizeX, float sizeY, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);
sf::Sprite initSprite(Size sizeOfSprite, std::string pathToSprite, Position spritePosition, sf::Texture *spriteTexture);
PlatformView createPlatform(float sizeX, float sizeY, std::string pathToPlatform, Position platformPosition, sf::Texture *platformTexture);
PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture);

#endif // INITIALIZER_H
