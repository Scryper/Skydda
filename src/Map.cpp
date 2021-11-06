#include "Map.h"

Map::Map() { }

Map::~Map() { }

Map::Map(const Map& other) { }

Map& Map::operator=(const Map& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
