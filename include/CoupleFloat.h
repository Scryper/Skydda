#ifndef COUPLEFLOAT_H
#define COUPLEFLOAT_H
#include <iostream>

class CoupleFloat {
    private:
        float x;
        float y;

    public:
        CoupleFloat();
        CoupleFloat(float x, float y);
        virtual ~CoupleFloat();
        CoupleFloat(const CoupleFloat& other);

        float getX()const;
        float getY()const;

        void setX(float x);
        void setY(float y);

};

#endif // COUPLEFLOAT_H
