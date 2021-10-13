#ifndef COUPLEFLOAT_H
#define COUPLEFLOAT_H


class CoupleFloat {
    private:
        float x;
        float y;

    public:
        CoupleFloat(float x=0., float y=0.);
        virtual ~CoupleFloat();
        CoupleFloat(const CoupleFloat& other);

        float getX()const;
        float getY()const;

        void setX(float x);
        void setY(float y);

};

#endif // COUPLEFLOAT_H
