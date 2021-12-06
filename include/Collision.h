#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <math.h>

#include "PlayerView.h"
#include "PlatformView.h"
#include "EnumCollision.h"

CollisionVector directionCollision(PlayerView player, PlatformView platform);

CollisionVector directionCollisionPlayers(PlayerView player1, PlayerView player2);

std::vector<CollisionVector> directionCollisions(PlayerView player, std::vector<PlatformView> platforms);

#endif // COLLISION_H
