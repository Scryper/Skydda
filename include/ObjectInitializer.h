#ifndef OBJECTINITIALIZER_H
#define OBJECTINITIALIZER_H

#include <vector>

#include "SpriteInitializer.h"
#include "PlatformView.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerView.h"
#include "HealthBarView.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, Position platformPosition, sf::Texture *platformTexture);

// creates the top, left and right plateform
std::vector<PlatformView> createBorders(sf::Texture *platformTexture);

//creates the player
PlayerView createPlayer(float sizeX,
                        float sizeY,
                        float width,
                        float height,
                        std::string pathToPlayer,
                        Position playerPosition,
                        sf::Texture *playerTexture,
                        sf::Keyboard::Key up,
                        sf::Keyboard::Key left,
                        sf::Keyboard::Key right,
                        sf::Keyboard::Key attack,
                        sf::Keyboard::Key protect,
                        sf::Keyboard::Key superAttack,
                        bool looksRight,
                        std::string namePlayerStr);

//Creates the healthBar
HealthBarView createHealthBar(Player player, Position posHealthBar);

#endif // OBJECTINITIALIZER_H
