#ifndef STATEPLAYER_H
#define STATEPLAYER_H

#include <map>
#include <SFML/Graphics.hpp>

typedef enum PlayerStateEnum{
    dead = 0, //define the first one to 1 will set others to 2,3,4...
    standby,
    defending,
    receiveDamage,
    attacking,
    jumping,
    movingLeft,
    movingRight,
    momentum,
    idle
}PlayerStateEnum;

typedef std::pair<PlayerStateEnum,int> PlayerStatePair;
typedef std::vector<PlayerStatePair*> PlayerStateBoolArray;

typedef std::pair<PlayerStateEnum, sf::Clock*> PlayerStateClock;
typedef std::vector<PlayerStateClock*> PlayerStateClockArray;



struct playerState{
    PlayerStateEnum state;
    bool isStateStackable;
    bool isTimed;
    bool onUserInput;
    bool isMovement;
    int animationDuration;
    int timeAction;
};

const std::vector<playerState> constPlayerStates
{   //STATE      STCK Tm   UI   MO  AD     TA
    {dead,          0,  0,  0,  0,  0,      0},
    {standby,       0,  0,  0,  0,  0,      0},
    {defending,     0,  1,  1,  0,  500,    0},
    {receiveDamage, 0,  1,  0,  0,  500,    0},
    {attacking,     0,  1,  1,  0,  1000,   700},
    {jumping,       0,  1,  1,  1,  1000,   0},
    {movingLeft,    0,  0,  1,  1,  0,      0},
    {movingRight,   0,  0,  1,  1,  0,      0},
    {momentum,      0,  0,  0,  0,  0,      0},
    {idle,          0,  0,  0,  0,  0,      0}
};

#endif // STATEPLAYER_H
