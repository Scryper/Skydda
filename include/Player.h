#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Position.h"
#include "Movement.h"

using namespace std;

class Player {
    private:
        string name;
        double attack;
        bool defense;
        double health;
        Position position;
        Movement movement;

    public:
        Player();
        Player(string name, double attack, bool defense, double health, Position position, Movement movement);
        Player(const Player& other);
        virtual ~Player();

        Movement getMovement() const;
        Position getPosition() const;

        void setPosition(Position position);
};

#endif // PLAYER_H
