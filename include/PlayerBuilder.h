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
        AND PlayerBuilder isn't copyable.*/
        PlayerBuilder* withName(std::string name);
        PlayerBuilder* withAttack(float attack);
        PlayerBuilder* withHealth(float health);
        PlayerBuilder* withPosition(Position position);
        PlayerBuilder* withMovement(Movement movement);
        PlayerBuilder* withPoints(int points);
};

#endif // PLAYERBUILDER_H
