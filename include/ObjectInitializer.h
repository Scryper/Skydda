#ifndef OBJECTINITIALIZER_H
#define OBJECTINITIALIZER_H

#include "SpriteInitializer.h"
#include "PlatformView.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerView.h"

#include <vector>

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, std::string pathToPlatform, Position platformPosition, sf::Texture *platformTexture);

// creates the top, left and right plateform
std::vector<PlatformView> createBorder(std::string pathToPlatform, sf::Texture *platformTexture);

//creates the player
PlayerView createPlayer(float sizeX, float sizeY, std::string pathToPlayer, Position playerPosition, sf::Texture *playerTexture);


#endif // OBJECTINITIALIZER_H
