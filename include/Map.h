#ifndef MAP_H
#define MAP_H

class Map {
    public:
        Map();
        virtual ~Map();
        Map(const Map& other);
        Map& operator=(const Map& other);
};

#endif // MAP_H
