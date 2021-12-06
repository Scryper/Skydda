#include "MusicManager.h"

std::mutex MusicManager::mutex_;

MusicManager::MusicManager() {
    if(!music.openFromFile("resources/audio/theme/fight_theme.ogg")) { // load audio
        std::cout << "Music was not found" << std::endl;
    }
    music.setVolume(GlobalVariables::VOLUME_MUSIC);
}

MusicManager* MusicManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_); // thread safe
    if(instance == nullptr) {
        instance = new MusicManager();
    }
    return instance;
}

void MusicManager::play() {
    music.play();
    music.setLoop(true); // music will start again when finished
}

void MusicManager::changeVolume(float newValue) {
    music.setVolume(newValue); // see optionscreen
}
