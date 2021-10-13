#ifndef SIZE_H
#define SIZE_H

#include "CoupleFloat.h"

class Size {
    private:
        CoupleFloat factor;

    public:
        Size();
        Size(CoupleFloat factor);
        Size(const Size& other);
        virtual ~Size();

        CoupleFloat getFactor() const;
        void setFactor(CoupleFloat couple);
};

#endif // SIZE_H
