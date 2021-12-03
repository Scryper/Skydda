#include "SoundManager.h"

std::mutex SoundManager::mutex_;

SoundManager::SoundManager() {
    // Death sounds
    sf::SoundBuffer bufferDeath;
    otherBuffers.insert(make_pair(DEATH_SOUND_PATH, bufferDeath));

    sf::Sound soundDeath;
    otherSounds.insert(make_pair(DEATH_SOUND_PATH, soundDeath));

    // Victory sound
    sf::SoundBuffer bufferVictory;
    otherBuffers.insert(make_pair(VICTORY_SOUND_PATH, bufferVictory));

    sf::Sound soundVictory;
    otherSounds.insert(make_pair(VICTORY_SOUND_PATH, soundVictory));

    // Hitting sounds
    for(int i = 1 ; i <= 10 ; i++) {
        sf::SoundBuffer buffer;
        hittingBuffers.insert(make_pair(PATH_HITS + std::to_string(i) + EXTENSION, buffer));

        sf::Sound sound;
        hittingSounds.insert(make_pair(PATH_HITS + std::to_string(i) + EXTENSION, sound));
    }
}

SoundManager* SoundManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::playSound(std::string path, std::map<std::string, sf::SoundBuffer> &buffers, std::map<std::string, sf::Sound> &sounds) {
    bool loadOk = buffers[path].loadFromFile(path);
    if(!loadOk) {
        std::cout << ERROR_TEXT + path << std::endl;
    }
    sounds[path] = sf::Sound{buffers[path]};
    sounds[path].play();
}

void SoundManager::playRandomHittingSound() {
    std::random_device random_dev;
    std::mt19937 rng(random_dev());
    std::uniform_int_distribution<int> dist(1, 10);

    int random = dist(rng);

    std::string path = PATH_HITS + std::to_string(random) + EXTENSION;

    playSound(path, hittingBuffers, hittingSounds);
}

void SoundManager::playDeathSound() {
    playSound(DEATH_SOUND_PATH, otherBuffers, otherSounds);
}

void SoundManager::playVictorySound() {
    playSound(VICTORY_SOUND_PATH, otherBuffers, otherSounds);
}
