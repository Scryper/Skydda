#ifndef PLAYERBUILDER_H
#define PLAYERBUILDER_H

#include "Player.h"
#include "Position.h"
#include "Movement.h"

class PlayerBuilder {
    private:
        Player player;

    public:
        PlayerBuilder();
        virtual ~PlayerBuilder();
        PlayerBuilder(const PlayerBuilder& other) = delete;
        PlayerBuilder& operator=(const PlayerBuilder& other) = delete;

        PlayerBuilder* reset();
        Player build();

        /*We send a pointer of the current instance to work on the same builder
        AND PlayerBuilder isn't copyable.
        
        There is 2 reasons to this : if we return Player -> player has no with... methods
        if we return void : we can't call a method on void.*/
        PlayerBuilder* withName(std::string name);
        PlayerBuilder* withAttack(float attack);
        PlayerBuilder* withHealth(float health);
        PlayerBuilder* withPosition(Position position);
        PlayerBuilder* withMovement(Movement movement);
        PlayerBuilder* withPoints(int points);
};

#endif // PLAYERBUILDER_H
