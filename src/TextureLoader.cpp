#include "TextureLoader.h"

sf::Sprite loadTexture(std::string path, Size size_, Position position, sf::Texture& texture) {
    if(!texture.loadFromFile(path)) {
        std::cout << "Texture was not found at " << path << std::endl;
    }
    sf::Sprite sprite(texture);
    sprite.setScale(size_.getFactor().getX(), size_.getFactor().getY());
    // set the origin of the image to its center
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
    sprite.setPosition(position.getX(), position.getY());
    return sprite;
}
