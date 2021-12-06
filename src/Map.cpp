#include "Map.h"

Map::Map() {
    this->mapSeed = 0;
}

Map::Map(int mapSeed) {
    this->mapSeed = mapSeed;
}

Map::~Map() { }

Map::Map(const Map& other) {
    this->mapSeed = other.mapSeed;
}

Map& Map::operator=(const Map& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->mapSeed = rhs.mapSeed;
    return *this;
}

///Getter
int Map::getMapSeed() {
    return mapSeed;
}
