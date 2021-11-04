#ifndef COLLISION_H
#define COLLISION_H

#include "PlayerView.h"
#include "PlatformView.h"
#include <vector>

std::vector<int> directionCollision(PlayerView player, PlatformView platform);

std::vector<int> directionCollisionPlayers(PlayerView player, PlayerView platform);

std::vector<std::vector<int>> directionCollisions(PlayerView player, std::vector<PlatformView> platform);

#endif // COLLISION_H
