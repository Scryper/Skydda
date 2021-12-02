#include "Player.h"

Player::Player() {
    this->name = "Inconnu";
    this->attack = 0.0;
    this->health = 0.0;
    Position defaultPosition = Position();
    Movement defaultMovement;
    this->position = defaultPosition;
    this->movement = defaultMovement;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();

}

Player::Player(std::string name, float attack, float health, Position position, Movement movement) {
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->position = position;
    this->movement = movement;
    timeLastAttack = 0;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->attack = other.attack;
    this->health = other.health;
    this->position = other.position;
    this->movement = other.movement;
    timeLastAttack = 0;
    durationBetweenAttacks = 1000;
    stateInitializer();
}

Player::~Player() {
    //stateDestroyer();
}

Movement Player::getMovement() const {
    return movement;
}

Position Player::getPosition() const {
    return position;
}

void Player::setPosition(Position position) {
    this->position = position;
}

void Player::setPosition(float x, float y) {
    Position position(x,y);
    this->position = position;
}

void Player::setHealth(float health) {
    this->health = health;
}

void Player::attackPlayer(Player &player, float clock) {
    //vérif que le player ne bloque pas l'attaque
    if(player.getState(defending) == true){
        timeLastAttack = clock;
        return;
    }

    // verifiy that player's health > 0
    if(player.getHealth() <= 0){
        timeLastAttack = clock;
        return;
    }

    //fa attack animation
    if(clock - timeLastAttack >= durationBetweenAttacks){
        // deal damages
        double health = player.getHealth();
        if(health - attack > 0) {
            player.setHealth(health - attack);
        }
        else {
            player.setHealth(0.f);
        }
        timeLastAttack = clock;
    }
}

std::string Player::getName()const {
    return name;
}

float Player::getHealth()const {
    return health;
}

float Player::getAttack()const{
    return attack;
}

void Player::stateInitializer(){
    initStatePointer(dead, 0);
    initStatePointer(standby,0);
    initStatePointer(defending,0);
    initStatePointer(receiveDamage,0);
    initStatePointer(attacking,0);
    initStatePointer(jumping,0);
    initStatePointer(movingLeft,0);
    initStatePointer(movingRight,0);
    initStatePointer(idle,1);
}

void Player::initStatePointer(playerStatePriority s, int val){
    PlayerStatePair *temp(0);
    temp = new PlayerStatePair;
    PlayerStatePair temp2 = {s,val};
    *temp = temp2;
    state.push_back(temp);
}

void Player::stateDestroyer(){
    for (auto i : state){
        delete i;
    }
}

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<std::vector<std::vector<int>>> collisions, bool noTP) {
    return movement.updatePosition(position, direction, collisions, noTP);
}

void Player::setState(playerStatePriority s, bool value){
     for(auto itStates : state){
        if(itStates->first==s){
            itStates->second=value;
        }
     }
}

bool Player::getState(playerStatePriority s)const{
    for(auto itStates : state){
        if(itStates->first==s){
            return itStates->second;
        }
     }
     return 0;
}

PlayerStateBoolArray Player::computeStates(std::vector<playerStatePriority> keyPressed){
    std::cout<<"ici"<<std::endl;

    //on parcourt tous les états dans l'ordre croissant d'importance
    for(auto itStates : state){
        //vérif si l'état est activé
        if(itStates->second==1){
            //verif si l'état n'est pas timed
            for(auto itConstPlayerStates : constPlayerStates){
                if(itConstPlayerStates.state == itStates->first && itConstPlayerStates.isTimed == 0){
                    //vérif si based on user input
                    if(itConstPlayerStates.onUserInput == 1){
                        //vérif si la key n'est pas pressed down
                        bool pressed = 0;
                        for(auto statePressed : keyPressed){
                            if(statePressed == itStates->first){
                                pressed = 1;
                            }
                        }
                        if (pressed == 0){
                            itStates->second = 0;
                        }
                    }
                }
            }

        }
        //l'état n'est pas activé
        else{
            //vérif si based on user input
            for(auto itConstPlayerStates : constPlayerStates){
                if(itConstPlayerStates.onUserInput == 1){
                    //verif si la key is pressed
                    for(auto statePressed : keyPressed){
                        if(statePressed == itStates->first){
                            //change state to true
                            itStates->second = 1;
                        }
                    }
                }
            }
        }
    }

    //on parcourt tous les états dans l'ordre croissant d'importance
    bool notStackable = 0;
    bool activated = 0;
    for(auto itStates : state){
        //si noStackable = 0
        if(notStackable == 0){
            //si état activé
            if(itStates->second==1){
                 if(itStates->first!=idle){
                    activated = 1;
                 }
                 for(auto itConstPlayerStates : constPlayerStates){
                    //si not stackable
                    if(itConstPlayerStates.state==itStates->first && itConstPlayerStates.isStateStackable == 0){
                        notStackable = 1;
                    }
                 }
            }
        }
        else{
            //desactivate state
            itStates->second = 0;
        }
    }

    //si aucun état n'est activé, c'est idle
    for(auto itStates : state){
        if(itStates->first==idle){
            if(activated==0){
                itStates->second=1;
            }
            else{
                itStates->second=0;
            }
        }
    }

    return state;
}


