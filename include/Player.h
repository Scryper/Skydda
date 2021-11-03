#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Position.h"
#include "Movement.h"

/*This class represents a player.*/
class Player {
    private:
        std::string name;
        double attack;
        bool defense;
        double health;
        Position position;
        Movement movement;

    public:
        Player();
        Player(std::string name, double attack, bool defense, double health, Position position, Movement movement);
        Player(const Player& other);
        virtual ~Player();

        Movement getMovement() const;
        Position getPosition() const;

        void stopX();
        void stopY();

        void setPosition(Position position);
        Position updatePosition(Position position, CoupleFloat coupleFloat,int collision);
};

#endif // PLAYER_H
