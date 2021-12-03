#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <random>
#include <iostream>
#include <map>
#include <mutex>

class SoundManager {
    private:
        SoundManager();

        static inline SoundManager* instance = nullptr;
        static std::mutex mutex_;

        std::map<std::string, sf::SoundBuffer> buffers;
        std::map<std::string, sf::Sound> sounds;

    public:
        SoundManager(const SoundManager& other) = delete;
        SoundManager& operator=(const SoundManager& other) = delete;

        static SoundManager* getInstance();
        void playRandomSound();
};

#endif // SOUNDMANAGER_H
