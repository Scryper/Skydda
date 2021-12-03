#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "GlobalVariables.h"

#include <SFML/Audio.hpp>
#include <iostream>
#include <mutex>

class MusicManager {
    private:
        MusicManager();

        static inline MusicManager* instance = nullptr;
        static std::mutex mutex_;

        sf::Music music;

    public:
        MusicManager(const MusicManager& other) = delete;
        MusicManager& operator=(const MusicManager& other) = delete;

        static MusicManager* getInstance();

        void play();
        void changeVolume(float newValue);
};

#endif // MUSICMANAGER_H
