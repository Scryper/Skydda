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

void Player::attackPlayer(Player &player, float clock, int factor) {
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
        if(health - attack*factor > 0) {
            player.setHealth(health - attack*factor);
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
    initStatePointer(specialAttacking,0);
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

Position Player::updatePosition(Position position, CoupleFloat direction, std::vector<CollisionVector> collisions) {
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

void Player::getHit(int value){
    movement.recul(value);
};

PlayerStateBoolArray Player::computeStates(std::vector<PlayerStateEnum> keyPressed, bool bottomCollision){

    //on parcourt tous les états dans l'ordre
    for(auto itStates : state){
        //vérif si l'état est activé
        if(itStates->second==1){
            //verif si l'état n'est pas timed et qu'il dépend d'un user input
            if(constPlayerStates[itStates->first].isTimed==0
               && constPlayerStates[itStates->first].onUserInput==1){
                //vérif si la key n'est pas pressed down, si elle l'est on passe l'état a 1
                itStates->second = 0;
                if(isFoundInArray(keyPressed,itStates->first)) itStates->second = 1;
            }
            if(constPlayerStates[itStates->first].isTimed==0
               && constPlayerStates[itStates->first].onUserInput==0
               &&itStates->first == momentum){
                itStates->second=0;
               }

        }
        //l'état n'est pas activé
        else{
             //verif si l'état dépend d'un user input
            if(constPlayerStates[itStates->first].onUserInput==1){
                //vérif si la key n'est pas pressed down, si elle l'est on passe l'état a 1
                itStates->second = 0;
                if(isFoundInArray(keyPressed,itStates->first)) itStates->second = 1;
            }
        }
    }

    bool activated = 0;
    bool movmentStateActivated = 0;

    //permet de savoir si c'est un état de mouvement ou pas
    //on parcourt tous les états dans l'ordre croissant d'importance
    for(auto itStates : state){
        if(activated==1){
            itStates->second=0;
        }
        //si état activé et que l'état n'est pas idle
        if(activated==0&&itStates->second==1&& itStates->first!=idle){
            //état est activé
            activated = 1;
            //si c'est un état de movement, movmentState -> true
            if(constPlayerStates[itStates->first].isMovement==1) movmentStateActivated = true;
        }

    }
    //si pas de movementState ET vitesse horizontale et verticale != 0
    /// ou bien qu'il n'y a pas de collision en dessous du player et pas de mouvement
    if(( movmentStateActivated!=1 && (movement.getSpeed().getX()!=0||movement.getSpeed().getY()!=0))||(bottomCollision==false && movmentStateActivated!=1)){
        state[momentum]->second=1;
    }

    //si aucun état activated, on set le state a idle
    activated = 0;
    for (auto i : state){
        if(i->second==1)activated=1;
    }

    if(!activated)state[idle]->second=1;


    //for(auto i : state){
        //cout<<i->first<<" "<<i->second<<endl;
    //}

    return state;
}

template <typename T>
bool Player::isFoundInArray(std::vector<T> vect, T element){
    return std::find(vect.begin(), vect.end(), element) != vect.end();
}
