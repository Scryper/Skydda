#include "PlayerViewBuilder.h"

PlayerViewBuilder::PlayerViewBuilder() {
    this->reset();
}

PlayerViewBuilder::~PlayerViewBuilder() { }

PlayerViewBuilder* PlayerViewBuilder::reset() {
    this->playerView = PlayerView();
    return this;
}


PlayerView PlayerViewBuilder::build() {
    return this->playerView;
}

PlayerViewBuilder* PlayerViewBuilder::withSprite(CoupleFloat size_, CoupleFloat center, std::string pathToPlayer, Position position, sf::Texture &texture) {
    PlayerSprite sprite = initSpritePlayer(size_, center, pathToPlayer, position, &texture);
    this->playerView.setSprite(sprite);
    return this;
}

PlayerViewBuilder* PlayerViewBuilder::withPlayer(Player player) {
    this->playerView.setPlayer(player);
    return this;
}

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

PlayerViewBuilder* PlayerViewBuilder::withLooksRight(bool looksRight) {
    this->playerView.setLooksRigth(looksRight);
    return this;
}
