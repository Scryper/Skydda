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

        const std::string ERROR_TEXT = "Audio resources was not found at : ";

        const static int NUMBER_OF_SOUNDS = 10;

        std::map<std::string, sf::SoundBuffer> hittingBuffers;
        std::map<std::string, sf::Sound> hittingSounds;
        const static inline std::string PATH_HITS = "resources/audio/fight/hits/hit";
        const static inline std::string EXTENSION = ".ogg";

        std::map<std::string, sf::SoundBuffer> otherBuffers;
        std::map<std::string, sf::Sound> otherSounds;
        const static inline std::string DEATH_SOUND_PATH = "resources/audio/fight/death/death.ogg";
        const static inline std::string VICTORY_SOUND_PATH = "resources/audio/victory/victory.ogg";

        void playSound(std::string path, std::map<std::string, sf::SoundBuffer> &buffers, std::map<std::string, sf::Sound> &sounds);

    public:
        SoundManager(const SoundManager& other) = delete;
        SoundManager& operator=(const SoundManager& other) = delete;

        static SoundManager* getInstance();
        void playRandomHittingSound();
        void playDeathSound();
        void playVictorySound();
};

#endif // SOUNDMANAGER_H
