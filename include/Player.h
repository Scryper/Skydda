#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Position.h"
#include "Movement.h"
#include "SoundLoader.h"

/*This class represents a player.*/
class Player {
    private:

        ///summarise the actual state of the player
        //0 = alive
        //1 = defense
        //2 = attack
        //3 = jumping
        //4 = moving left
        //5 = moving Rigth
        //6 = idle
        std::vector<bool> state;
        std::string name;
        float attack;
        int timeLastAttack;
        int durationBetweenAttacks;
        float health;
        Position position;
        Movement movement;

    public:
        Player();
        Player(std::string name, float attack, float health, Position position, Movement movement);

        Player(const Player& other);
        virtual ~Player();

        Movement getMovement() const;
        Position getPosition() const;

        float getHealth()const;
        std::string getName()const;

        std::vector<bool>& getState();

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
        Position updatePosition(Position position, CoupleFloat coupleFloat, std::vector<std::vector<std::vector<int>>> collisions, bool noTP);
};

#endif // PLAYER_H
