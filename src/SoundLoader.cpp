#include "SoundLoader.h"

void SoundLoader::playRandomSound() {
    std::random_device random_dev;
    std::mt19937 rng(random_dev());
    std::uniform_int_distribution<int> dist(1, 8);

    int random = dist(rng);

    std::string path = "";
    sf::SoundBuffer buffer;

    switch(random) {
        case 1:
            path = "resources/audio/fight/hits/hit1.ogg";
            break;
        case 2:
            path = "resources/audio/fight/hits/hit2.ogg";
            break;
        case 3:
            path = "resources/audio/fight/hits/hit3.ogg";
            break;
        case 4:
            path = "resources/audio/fight/hits/hit4.ogg";
            break;
        case 5:
            path = "resources/audio/fight/hits/hit5.ogg";
            break;
        case 6:
            path = "resources/audio/fight/hits/hit6.ogg";
            break;
        case 7:
            path = "resources/audio/fight/hits/hit7.ogg";
            break;
        case 8:
            path = "resources/audio/fight/hits/hit8.ogg";
            break;
        default:
            path = "resources/audio/fight/hits/hit1.ogg";
            break;
    }
    std::cout << path << std::endl;

    if(!buffer.loadFromFile(path)) {
        std::cout << "Sound was not found at " << path << std::endl;
    }
    sf::Sound sound(buffer);
    sound.play();
}
