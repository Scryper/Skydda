#ifndef MAP_H
#define MAP_H
#include "CoupleFloat.h"

class Map {
    private:
        int mapSeed;
    public:
        Map();
        Map(int seed);
        virtual ~Map();
        Map(const Map& other);
        Map& operator=(const Map& other);

        ///Getter
        int getMapSeed();
};

#endif // MAP_H
