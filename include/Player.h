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
        int timeLastAttack;
        int durationBetweenAttacks;
        bool defense;
        bool alive;
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
        void setDefense(bool def);
        float getAttack()const;

        void attackPlayer(Player& p, float clock);

        void stopX();
        void stopY();

        bool isAlive()const;
        void setAlive(bool alive);

        void setPosition(Position position);
        void setPosition(float x, float y);
        Position updatePosition(Position position, CoupleFloat coupleFloat,std::vector<std::vector<std::vector<int>>> collisions);
};

#endif // PLAYER_H
