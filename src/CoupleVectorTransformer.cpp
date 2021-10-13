#include "CoupleVectorTransformer.h"

sf::Vector2f coupleToVector(CoupleFloat couple) {
    sf::Vector2f vector2f(couple.getX(), couple.getY());
    return vector2f;
}

CoupleFloat vectorToCouple(sf::Vector2f vector2f) {
    CoupleFloat couple(vector2f.x, vector2f.y);
    return couple;
}
