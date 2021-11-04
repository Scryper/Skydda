#include "PlayerView.h"
#include "Collision.h"

PlayerView::PlayerView() {
    sf::Sprite defaultSprite;
    this->sprite = defaultSprite;
    Player defaultPlayer;
    this->player = defaultPlayer;
    /*this->texture.loadFromFile("resources/images/character/test.png");
    this->sprite.setTexture(texture);
    sf::IntRect rectSourceSprite(0, 0, 80, 40);
    this->sprite.setTextureRect(rectSourceSprite);
    tour = 0;*/
}

PlayerView::PlayerView(sf::Sprite sprite, Player player,sf::Keyboard::Key up, sf::Keyboard::Key left, sf::Keyboard::Key right,sf::Keyboard::Key attack) {
    this->sprite = sprite;
    this->player = player;
    this->up = up;
    this->left = left;
    this->right = right;
    this->attackKey = attack;
    this->looksRight = true;
    /*this->texture.loadFromFile("resources/images/character/test.png");
    this->sprite.setTexture(texture);
    sf::IntRect rectSourceSprite(0, 0, 80, 40);
    this->sprite.setTextureRect(rectSourceSprite);
        tour = 0;
*/
}

PlayerView::PlayerView(const PlayerView& other) {
    this->sprite = other.sprite;
    this->player = other.player;
    /*this->texture.loadFromFile("resources/images/character/test.png");
    this->sprite.setTexture(texture);
    sf::IntRect rectSourceSprite(0, 0, 80, 40);
    this->sprite.setTextureRect(rectSourceSprite);
        tour = 0;
*/
}

PlayerView::~PlayerView() { }

Player& PlayerView::getPlayer() {
    return player;
}

sf::Sprite PlayerView::getSprite() const {
    return sprite;
}

void PlayerView::setAlive(bool alive) {
    player.setAlive(alive);
}

bool PlayerView::isLooksRigth()const{
    return looksRight;
}

Position PlayerView::computeNewPosition(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions){
    return player.updatePosition(player.getPosition(), vectorToCouple(vectorDirection), collisions);
}

void PlayerView::movePlayer(sf::Vector2f vectorDirection, std::vector<std::vector<std::vector<int>>> collisions) {
    // we swap the player's sprite if he is not looking the way he is going
    if((looksRight && vectorDirection.x < 0) || (!looksRight && vectorDirection.x > 0)) {
        sprite.scale(-1.f, 1.f);
        looksRight = !looksRight; // to know where he is looking
    }

    Position newPosition = computeNewPosition(vectorDirection, collisions);
    player.setPosition(newPosition);
    sprite.setPosition(newPosition.getX(), newPosition.getY());

}

sf::Vector2f PlayerView::inputPlayer(float deltaTime, PlayerView &p2){
    /*if (this->clock.getElapsedTime().asSeconds() >= 2.0f){

        if (this->tour == 3){
            this->tour = 0;
        }
        else{
            this->tour += 1;
        }
        this->sprite.setTextureRect(sf::IntRect(tour*80, 0, 80, 40));
        this->clock.restart();
    }*/

     sf::Vector2f vector2f(0.f, 0.f);

     if(player.isAlive()) {

        if(sf::Keyboard::isKeyPressed(up)) {
            vector2f.y += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(left)) {
            vector2f.x += -deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(right)) {
            vector2f.x += deltaTime;
        }
        if(sf::Keyboard::isKeyPressed(attackKey)){
            //vérif s'il y a une collision, si oui on peut lancer l'appel de la fonction
            //la direction de l'attaque n'est pas encore gérée
            std::vector<std::vector<int>> collision = directionCollisionPlayers(*this,p2);
            if(collision.size()>0 && collision[0][0]>0){
                std::cout<<"attaké  "<< collision[0][0] <<endl;
                attack(p2);

             }
        }
    }
    return vector2f;
}

void PlayerView::attack(PlayerView &playerAttacked){
    cout<<playerAttacked.player.getHealth()<<endl;
    //vérif que le player ne bloque pas l'attaque
    if(playerAttacked.getPlayer().getDefense()==true)
        return;
    //vérif que les pv sont supérieur a 0
    if(playerAttacked.getPlayer().getHealth()<=0)
        return;
    //faire l'animation d'attaque

    //retirer les PV
    double health = playerAttacked.player.getHealth();
    if(health-player.getAttack()>0){
        playerAttacked.player.setHealth(health-player.getAttack());
    }
    else{
        playerAttacked.player.setHealth(0.f);
    }

    //delai????
}

void PlayerView::setHealth(float health) {
    player.setHealth(health);
}

