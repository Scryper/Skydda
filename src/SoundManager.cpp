#include "SoundManager.h"

std::mutex SoundManager::mutex_;

/*create empty buffers and sound objects and link them with the path of the sound*/
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
    for(int i = 1 ; i <= NUMBER_OF_SOUNDS ; i++) {
        sf::SoundBuffer buffer;
        hittingBuffers.insert(make_pair(PATH_HITS + std::to_string(i) + EXTENSION, buffer));

        sf::Sound sound;
        hittingSounds.insert(make_pair(PATH_HITS + std::to_string(i) + EXTENSION, sound));
    }
}

// Sound manager is not copyable
// So to be able to use it via the getInstance Method, we send a pointer of the object
// So the call should be SoundManager* var = SoundManager::getInstance(); 
// and not SoundManager var = SoundManager::getInstance();
// As the second option will attempt to make a copy because of "="
// The ability to make a copy of this singleton object, will break the singleton aspect of this object
// This is why SoundManager is not copyable
SoundManager* SoundManager::getInstance() { 
    std::lock_guard<std::mutex> lock(mutex_); // allows the singleton to be thread safe
    if(instance == nullptr) { // if there is no instance of the object
        instance = new SoundManager(); // initialize the instance
    }
    return instance; // return the instance
}

void SoundManager::playSound(std::string path, std::map<std::string, sf::SoundBuffer> &buffers, std::map<std::string, sf::Sound> &sounds) {
    bool loadOk = buffers[path].loadFromFile(path); // load the sound
    if(!loadOk) {
        std::cout << ERROR_TEXT + path << std::endl;
    }
    sounds[path] = sf::Sound{buffers[path]}; // apply it to sf::sound
    sounds[path].play(); // play the sound
}

void SoundManager::playRandomHittingSound() {
    // get a random number between 1 and 10, and then play the hitx sound
    // with x the random number
    std::random_device random_dev;
    std::mt19937 rng(random_dev());
    std::uniform_int_distribution<int> dist(1, 10);

    int random = dist(rng);
    //               resources/audio/...                       .ogg
    std::string path = PATH_HITS + std::to_string(random) + EXTENSION;

    playSound(path, hittingBuffers, hittingSounds);
}

void SoundManager::playDeathSound() {
    playSound(DEATH_SOUND_PATH, otherBuffers, otherSounds);
}

void SoundManager::playVictorySound() {
    playSound(VICTORY_SOUND_PATH, otherBuffers, otherSounds);
}
