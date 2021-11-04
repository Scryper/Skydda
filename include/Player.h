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
        float attack;
        float timeLastAttack;
        bool defense;
        float health;
        Position position;
        Movement movement;

    public:
        Player();
        Player(std::string name, float attack, bool defense, float health, Position position, Movement movement);

        Player(const Player& other);
        virtual ~Player();

        Movement getMovement() const;
        Position getPosition() const;

        float getHealth()const;
        string getName()const;

        void setHealth(float health);

        bool getDefense()const;
        float getAttack()const;

        void stopX();
        void stopY();

        void setPosition(Position position);
        Position updatePosition(Position position, CoupleFloat coupleFloat,std::vector<std::vector<int>> collisions);
};

#endif // PLAYER_H
