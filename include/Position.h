#ifndef POSITION_H
#define POSITION_H

#include <iostream>

/*This class is used to manage the position of players and their sprites.*/
class Position {
    private:
        int x;
        int y;

    public:
        Position(int x = 0, int y = 0);
        Position(const Position& other);
        virtual ~Position();

        int getX() const;
        int getY() const;

        void setX(int x);
        void setY(int y);
};

#endif // POSITION_H
