#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Size.h"
#include "Position.h"

sf::Sprite loadTexture(std::string path, Size size_, Position position, sf::Texture& texture);

#endif // TEXTURELOADER_H
