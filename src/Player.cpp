#include "Player.h"

Player::Player() {
    //cout<<"Constructeur player"<<endl;
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
    //cout<<"Constructeur player"<<endl;
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
    //cout<<"Constructeur player"<<endl;
}

Player::~Player() {
    //cout<<"destructeur player"<<endl;
    //stateDestroyer();
    //for (PlayerStatePair* p : state ){
        //delete p;
    //}
    state.clear();
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
    initStatePointer(momentum,1);
    initStatePointer(idle,0);
}

void Player::initStatePointer(PlayerStateEnum s, int val){
    PlayerStatePair *temp;
    temp = new PlayerStatePair{s,val};
    state.push_back(temp);
}

void Player::stateDestroyer(){
    //for()
    //state.clear();
}

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<std::vector<std::vector<int>>> collisions) {
    return movement.updatePosition(position, direction, collisions);
}

void Player::setState(PlayerStateEnum s, bool value){
     for(auto itStates : state){
        if(itStates->first==s){
            itStates->second=value;
        }
     }
}

bool Player::getState(PlayerStateEnum s)const{
    for(auto itStates : state){
        if(itStates->first==s){
            return itStates->second;
        }
     }
     return 0;
}

PlayerStateBoolArray Player::computeStates(std::vector<PlayerStateEnum> keyPressed){
    //si pas en train de défendre -> change state
    bool def = 0;
    for(auto i : keyPressed){
        if(i== defending)def = 1;
    }
    if(!def){
        for (auto itStates : state){
            if (itStates->first == defending)
                itStates->second = 0;
        }
    }



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
    bool movmentStateActivated = 0;
    for(auto itStates : state){
        //si noStackable = 0
        if(notStackable == 0){
            //si état activé
            if(itStates->second==1){
                 if(itStates->first!=idle){
                    activated = 1;
                    for(auto itConstPlayerStates : constPlayerStates){
                        if(itConstPlayerStates.state==itStates->first && itConstPlayerStates.isMovement == 1){
                            movmentStateActivated = 1;
                        }
                    }
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

    //si pas de movementState ET vitesse horizontale et verticale != 0 ou bien qu'il n'y a pas de collision en dessous du player
    if(movmentStateActivated!=1 && (movement.getSpeed().getX()!=0||movement.getSpeed().getY()!=0)){
        for(auto itStates : state){
            if(itStates->first==momentum){
                itStates->second=1;
            }
        }
    }

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


