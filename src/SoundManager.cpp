#include "SoundManager.h"

std::mutex SoundManager::mutex_;

SoundManager::SoundManager() {
    for(int i = 1 ; i <= 10 ; i++) {
        sf::SoundBuffer buffer;
        buffers.insert(make_pair("resources/audio/fight/hits/hit" + std::to_string(i) + ".ogg", buffer));

        sf::Sound sound;
        sounds.insert(make_pair("resources/audio/fight/hits/hit" + std::to_string(i) + ".ogg", sound));
    }
}

SoundManager* SoundManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::playRandomSound() {
    std::random_device random_dev;
    std::mt19937 rng(random_dev());
    std::uniform_int_distribution<int> dist(1, 10);

    int random = dist(rng);

    std::string path = "resources/audio/fight/hits/hit" + std::to_string(random) + ".ogg";

    bool loadOk = buffers[path].loadFromFile(path);
    if(!loadOk) {
        std::cout << "Audio resources was not found at : " + path << std::endl;
    }
    sounds[path] = sf::Sound{buffers[path]};
    sounds[path].play();
}
