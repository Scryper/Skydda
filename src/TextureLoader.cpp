#include "TextureLoader.h"

sf::Sprite loadTexture(std::string path, sf::Texture& texture) {
    if(!texture.loadFromFile(path)) {
        std::cout << "Texture was not found at " << path << std::endl;
    }
    sf::Sprite sprite(texture);
    return sprite;
}
