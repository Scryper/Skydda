#ifndef EPLAYERONUSERINPUT_H
#define EPLAYERONUSERINPUT_H

#include <map>
#include <iostream>
#include "EPlayerStatePriority.h"

using namespace std;

std::map<playerStatePriority,int> test {{dead,0},
                                        {standby,0},
                                        {defending,1},
                                        {receiveDamage,0},
                                        {attacking,1},
                                        {jumping,1},
                                        {movingLeft,1},
                                        {movingRight,1},
                                        {idle,0}
};
#endif // EPLAYERONUSERINPUT_H
