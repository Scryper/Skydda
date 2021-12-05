#ifndef OBJECTINITIALIZER_H
#define OBJECTINITIALIZER_H

#include <vector>

#include "SpriteInitializer.h"
#include "PlatformView.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerView.h"
#include "PlayerViewBuilder.h"
#include "HealthBarView.h"
#include "PlayerBuilder.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, Position platformPosition, sf::Texture *platformTexture);

// creates the top, left and right plateform
std::vector<PlatformView> createBorders(sf::Texture *platformTexture);

//Creates the healthBar
HealthBarView createHealthBar(Player player, Position posHealthBar);

#endif // OBJECTINITIALIZER_H
