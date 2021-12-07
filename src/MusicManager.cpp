#include "MusicManager.h"

std::mutex MusicManager::mutex_;

MusicManager::MusicManager() {
    if(!music.openFromFile("resources/audio/theme/fight_theme.ogg")) { // load audio
        std::cout << "Music was not found" << std::endl;
    }
    music.setVolume(GlobalVariables::VOLUME_MUSIC);
}

// Sound manager is not copyable
// So to be able to use it via the getInstance Method, we send a pointer of the object
// So the call should be SoundManager* var = SoundManager::getInstance(); 
// and not SoundManager var = SoundManager::getInstance();
// As the second option will attempt to make a copy because of "="
// The ability to make a copy of this singleton object, will break the singleton aspect of this object
// This is why SoundManager is not copyable
MusicManager* MusicManager::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_); // allows the singleton to be thread safe
    if(instance == nullptr) { // if there is no instance of the object
        instance = new MusicManager();
    }
    return instance; // return the instance
}

void MusicManager::play() {
    music.play();
    music.setLoop(true); // music will start again when finished
}

void MusicManager::changeVolume(float newValue) {
    music.setVolume(newValue); // see optionscreen
}
