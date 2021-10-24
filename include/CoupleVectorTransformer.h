#ifndef COUPLEVECTORTRANSFORMER_H
#define COUPLEVECTORTRANSFORMER_H

#include <SFML/Graphics.hpp>
#include "CoupleFloat.h"

/*This methods transform a couple of float into a vector or a vector into a couple of float.
Allows to switch between model and view.*/
sf::Vector2f coupleToVector(CoupleFloat couple);
CoupleFloat vectorToCouple(sf::Vector2f vector2f);

#endif // COUPLEVECTORTRANSFORMER_H
