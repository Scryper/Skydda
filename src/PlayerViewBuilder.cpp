#include "PlayerViewBuilder.h"

// The playerview is created automatically when we call the builder's constructor
PlayerViewBuilder::PlayerViewBuilder() {
    this->reset();
}

PlayerViewBuilder::~PlayerViewBuilder() { }

// sets or resets the playerview with the basic values (see default constructor of PlayerView.cpp)
PlayerViewBuilder* PlayerViewBuilder::reset() {
    this->playerView = PlayerView();
    return this; // allows to chain the methods
}

// This method is called at the end of the chain when the user has created the wanted playerview
PlayerView PlayerViewBuilder::build() {
    return this->playerView;
}

// create the sprite and affects it to the player
PlayerViewBuilder* PlayerViewBuilder::withSprite(CoupleFloat size_, CoupleFloat center, std::string pathToPlayer, Position position, sf::Texture &texture) {
    PlayerSprite sprite = initSpritePlayer(size_, center, pathToPlayer, position, &texture);
    this->playerView.setSprite(sprite);
    return this;
}

// affects the player that the vie has to show
PlayerViewBuilder* PlayerViewBuilder::withPlayer(Player player) {
    this->playerView.setPlayer(player);
    return this;
}

// link the keys of the player with the event they create
PlayerViewBuilder* PlayerViewBuilder::withKeys(
            sf::Keyboard::Key up,
            sf::Keyboard::Key left,
            sf::Keyboard::Key right,
            sf::Keyboard::Key attack,
            sf::Keyboard::Key protect,
            sf::Keyboard::Key superAttack) {
    std::vector<pair<PlayerStateEnum,sf::Keyboard::Key>> keys;
    keys.push_back({jumping,up});
    keys.push_back({movingLeft,left});
    keys.push_back({movingRight,right});
    keys.push_back({attacking,attack});
    keys.push_back({defending,protect});
    keys.push_back({specialAttacking,superAttack});

    this->playerView.setKeys(keys);
    return this;
}

// sets if, at the beginning of the game, the player looks at his right or left
PlayerViewBuilder* PlayerViewBuilder::withLooksRight(bool looksRight) {
    this->playerView.setLooksRigth(looksRight);
    return this;
}
