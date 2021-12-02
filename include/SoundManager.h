#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <random>
#include <iostream>

class SoundManager {
    public:
        SoundManager();
        virtual ~SoundManager();

        void playRandomSound();
};

#endif // SOUNDMANAGER_H
