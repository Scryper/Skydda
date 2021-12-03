#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Position.h"
#include "Movement.h"
#include "SoundLoader.h"
#include "StatePlayer.h"

using namespace std;

/*This class represents a player.*/
class Player {
    private:
        PlayerStateBoolArray state;
        string name;
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
        void stateDestroyer();
        void initStatePointer(PlayerStateEnum s, int val);

        Movement getMovement() const;
        Position getPosition() const;
        std::string getName()const;
        float getHealth()const;
        void setHealth(float health);
        float getAttack()const;
        void setPosition(Position position);
        void setPosition(float x, float y);
        void stateInitializer();
        void setState(PlayerStateEnum s, bool value);
        bool getState(PlayerStateEnum s)const;
        void getHit(int value);

        template <typename T>
        bool isFoundInArray(std::vector<T> vect, T element);


        void attackPlayer(Player& p, float clock);
        Position updatePosition(Position position, CoupleFloat coupleFloat, std::vector<std::vector<std::vector<int>>> collisions);
        PlayerStateBoolArray computeStates(std::vector<PlayerStateEnum> keyPressed, bool bottomCollision);

};

#endif // PLAYER_H
