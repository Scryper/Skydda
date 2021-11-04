#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Position.h"
#include "Movement.h"

using namespace std;

/*This class represents a player.*/
class Player {
    private:
        std::string name;
        double attack;
        double timeLastAttack;
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

        double getHealth()const;
        string getName()const;
        void setHealth(double health);
        bool getDefense()const;
        double getAttack()const;

        void stopX();
        void stopY();

        void setPosition(Position position);
        Position updatePosition(Position position, CoupleFloat coupleFloat,std::vector<std::vector<int>> collisions);
};

#endif // PLAYER_H
