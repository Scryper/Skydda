#ifndef COUPLEFLOAT_H
#define COUPLEFLOAT_H

#include <iostream>

/*This class represents a Vector of two values.
This class is used in model.*/
class CoupleFloat {
    private:
        float x;
        float y;

    public:
        CoupleFloat();
        CoupleFloat(float x, float y);
        virtual ~CoupleFloat();
        CoupleFloat(const CoupleFloat& other);
        CoupleFloat& operator=(const CoupleFloat& other);


        float getX()const;
        float getY()const;

        void setX(float x);
        void setY(float y);

};

#endif // COUPLEFLOAT_H
