#ifndef PLATFORM_H
#define PLATFORM_H

#include "Position.h"
#include "CoupleFloat.h"


class Platform {
    private:
        Position position;
        CoupleFloat size_; // underscore because size is a keyword

    public:
        Platform();
        Platform(const Position position, const CoupleFloat size_);
        ~Platform();
        Platform(const Platform& other);
        Platform& operator=(const Platform& other);

        ///Getter
        Position getPosition() const;
        CoupleFloat getSize() const;

        ///Setter
        void setPosition(Position position);
        void setSize(CoupleFloat size_);
};

#endif // PLATFORM_H
