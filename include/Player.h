#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Movement.h"
#include "StatePlayer.h"
#include "EnumCollision.h"

using namespace std;

/*This class represents a player.*/
class Player {
    private:
        PlayerStateBoolArray state;
        std::string name;
        float attack;
        int timeLastAttack;
        int durationBetweenAttacks;
        float health;
        int points;
        Position position;
        Movement movement;

        const static int MIN_ATTACK = 0;
        const static int MAX_ATTACK = 100;

    public:
        Player();
        Player(const Player& other);
        virtual ~Player();
        Player& operator=(const Player& other);
        void stateDestroyer();
        void initStatePointer(PlayerStateEnum s, int val);
        void stateInitializer();

        void setPosition(Position position);
        void setPosition(float x, float y);
        void setSpeedX(float x);
        void setState(PlayerStateEnum s, bool value);
        void setHealth(float health);
        void setAttack(float attack_);
        void setName(std::string name_);
        void setMovement(Movement movement_);
        void setPoints(int points);

        bool getState(PlayerStateEnum s)const;
        void getHit(int value);
        float getAttack()const;
        float getHealth()const;
        Movement getMovement() const;
        Position getPosition() const;
        std::string getName()const;
        int getPoints()const;

        template <typename T>
        bool isFoundInArray(std::vector<T> vect, T element);

        void attackPlayer(Player& p, float clock, int factor, bool directionAttack, bool directionProtection);

        Position updatePosition(Position position, CoupleFloat coupleFloat, std::vector<CollisionVector> collisions);

        PlayerStateBoolArray computeStates(std::vector<PlayerStateEnum> keyPressed, bool bottomCollision);
};

#endif // PLAYER_H
