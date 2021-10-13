#ifndef COUPLEVECTORTRANSFORMER_H
#define COUPLEVECTORTRANSFORMER_H

#include <SFML/Graphics.hpp>
#include "CoupleFloat.h"

sf::Vector2f coupleToVector(CoupleFloat couple);
CoupleFloat vectorToCouple(sf::Vector2f vector2f);

#endif // COUPLEVECTORTRANSFORMER_H