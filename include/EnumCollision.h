#ifndef ENUMCOLLISION_H
#define ENUMCOLLISION_H


typedef enum CollisionEnum{
    bottom = 0,
    top,
    rigthCol,
    leftCol,
    incorrectCol
}CollisionEnum;

typedef std::pair<CollisionEnum,int> DisplacementPerCollision;
typedef std::vector<DisplacementPerCollision> CollisionVector;

#endif // ENUMCOLLISION_H
