#include "TextureLoader.h"

//load texture and print an error if the texture does not exist
sf::Sprite loadTexture(std::string path, sf::Texture& texture) {
    if(!texture.loadFromFile(path)) {
        std::cout << "Texture was not found at " << path << std::endl;
    }
    sf::Sprite sprite(texture);
    return sprite;
}
PlayerSprite loadTexturePlayer(std::string path, sf::Texture& texture) {
    if(!texture.loadFromFile(path)) {
        std::cout << "Texture was not found at " << path << std::endl;
    }
    PlayerSprite sprite(texture);


    return sprite;
}
