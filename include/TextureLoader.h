#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "PlayerSprite.h"

//Load the texture of a Sprite
sf::Sprite loadTexture(std::string path, sf::Texture& texture);

//Load the texture of a PlayerSprite
PlayerSprite loadTexturePlayer(std::string path, sf::Texture& texture);

#endif // TEXTURELOADER_H
