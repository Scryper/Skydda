#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <math.h>

#include "PlayerView.h"
#include "PlatformView.h"

std::vector<std::vector<int>> directionCollision(PlayerView player, PlatformView platform);

std::vector<std::vector<int>> directionCollisionPlayers(PlayerView player1, PlayerView player2);

std::vector<std::vector<std::vector<int>>> directionCollisions(PlayerView player, std::vector<PlatformView> platforms);

#endif // COLLISION_H
