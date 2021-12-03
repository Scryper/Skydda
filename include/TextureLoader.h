#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "PlayerSprite.h"

sf::Sprite loadTexture(std::string path, sf::Texture& texture);
PlayerSprite loadTexturePlayer(std::string path, sf::Texture& texture);

#endif // TEXTURELOADER_H
