#ifndef PLATFORM_H
#define PLATFORM_H

#include "Position.h"
#include "Size.h"

class Platform {
    private:
        Position position;
        Size size_; // underscore because size is a keyword

    public:
        Platform();
        Platform(const Position position, const Size size_);
        ~Platform();
        Platform(const Platform& other);
        Position getPosition() const;
        Size getSize() const;
        void setPosition(Position position);
        void setSize(Size size_);
};

#endif // PLATFORM_H
