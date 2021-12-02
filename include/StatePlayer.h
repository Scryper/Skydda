#ifndef STATEPLAYER_H
#define STATEPLAYER_H

#include <map>
#include <SFML/Graphics.hpp>

typedef enum playerStateEnum{
    dead = 0, //define the first one to 1 will set others to 2,3,4...
    standby,
    defending,
    receiveDamage,
    attacking,
    jumping,
    movingLeft,
    movingRight,
    idle
}playerStatePriority;

typedef std::pair<playerStateEnum,int> PlayerStatePair;
typedef std::vector<PlayerStatePair*> PlayerStateBoolArray;

typedef std::pair<playerStateEnum, sf::Clock> PlayerStateClock;
typedef std::vector<PlayerStateClock> PlayerStateClockArray;



struct playerState{
    playerStatePriority state;
    bool isStateStackable;
    bool isTimed;
    bool onUserInput;
    int animationDuration;
    int timeAction;
};

const std::vector<playerState> constPlayerStates
{   //STATE      STCK Tm   UI   AD     TA
    {dead,          0,  0,  0,  0,      0},
    {standby,       0,  0,  0,  0,      0},
    {defending,     0,  0,  1,  0,      0},
    {receiveDamage, 0,  1,  0,  500,    0},
    {attacking,     0,  1,  1,  1000,   700},
    {jumping,       1,  1,  1,  1000,   0},
    {movingLeft,    1,  0,  1,  0,      0},
    {movingRight,   1,  0,  1,  0,      0},
    {idle,          0,  0,  0,  0,      0}
};

#endif // STATEPLAYER_H
