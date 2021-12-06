#ifndef STATEPLAYER_H
#define STATEPLAYER_H

#include <map>
#include <SFML/Graphics.hpp>

typedef enum PlayerStateEnum{
    dead = 0, //define the first one to 1 will set others to 2,3,4...
    standby,
    defending,
    receiveDamage,
    specialAttacking,
    attacking,
    jumping,
    movingLeft,
    movingRight,
    momentum,
    idle
}PlayerStateEnum;

struct playerState{
    PlayerStateEnum state;
    bool isTimed;
    bool onUserInput;
    bool isMovement;
    bool isPlayedOneTime;
    int animationDuration;
    int timeAction;
};

struct animState{
    PlayerStateEnum state;
    int maxFrame;
    int row;
};

struct animStateTour{
    PlayerStateEnum state;
    int tour;
};

typedef std::pair<PlayerStateEnum,int> PlayerStatePair;
typedef std::vector<PlayerStatePair*> PlayerStateBoolArray;

typedef std::pair<PlayerStateEnum, sf::Clock*> PlayerStateClock;
typedef std::vector<PlayerStateClock*> PlayerStateClockArray;

typedef std::vector<animStateTour*> AnimStateTours;

const std::vector<playerState> constPlayerStates
{   //STATE             Tm  UI  MO otp  AD     TA
    {dead,              0,  0,  0,  1,  0,      0},
    {standby,           0,  0,  0,  0,  0,      0},
    {defending,         0,  1,  0,  1,  0,      0},
    {receiveDamage,     1,  0,  0,  1,  400,    0},
    {specialAttacking,  1,  1,  0,  1,  1000,   750},
    {attacking,         1,  1,  1,  1,  400,    250},
    {jumping,           1,  1,  1,  1,  900,   0},
    {movingLeft,        0,  1,  1,  0,  0,      0},
    {movingRight,       0,  1,  1,  0,  0,      0},
    {momentum,          0,  0,  0,  0,  0,      0},
    {idle,              0,  0,  0,  0,  0,      0}
};

const std::vector<animState> constAnimState
{
    {dead,              11,  1},
    {standby,           11,  3},
    {defending,         5,  6},
    {receiveDamage,     11,  2},
    {specialAttacking,  17,  7},
    {attacking,         7,  0},
    {jumping,           9,  4},
    {movingLeft,        11,  5},
    {movingRight,       11,  5},
    {momentum,          11,  3},
    {idle,              11,  3}
};


#endif // STATEPLAYER_H
