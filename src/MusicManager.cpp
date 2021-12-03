#include "MusicManager.h"

std::mutex MusicManager::mutex_;

MusicManager::MusicManager() {
    if(!music.openFromFile("resources/audio/theme/fight_theme.ogg")) {
        std::cout << "Music was not found" << std::endl;
    }
    music.setVolume(GlobalVariables::VOLUME_MUSIC);
}

MusicManager* MusicManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance == nullptr) {
        instance = new MusicManager();
    }
    return instance;
}

void MusicManager::play() {
    music.play();
    music.setLoop(true);
}

void MusicManager::changeVolume(float newValue) {
    music.setVolume(newValue);
}
