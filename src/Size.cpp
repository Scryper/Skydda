#include "Size.h"

Size::Size() { }

Size::Size(CoupleFloat factor_) : factor(factor_) { }

Size::Size(const Size& other) : factor(other.factor) { }

Size::~Size() { }

CoupleFloat Size::getFactor() const {
    return factor;
}

void Size::setFactor(CoupleFloat couple) {
    this->factor = couple;
}
