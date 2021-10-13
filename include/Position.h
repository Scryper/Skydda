#ifndef POSITION_H
#define POSITION_H


class Position {
    private:
        int x;
        int y;

    public:
        Position(int x = 0, int y = 0);
        Position(const Position& other);
        virtual ~Position();

        int getX()const;
        int getY()const;

        void setX(int x);
        void setY(int y);
};

#endif // POSITION_H
