#include "ObjectInitializer.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, Position platformPosition, sf::Texture *platformTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    CoupleFloat sizeOfSprite(sizeCouple);

    sf::Sprite platformSprite = initSprite(sizeOfSprite, platformPosition, platformTexture);

    Position viewPosition(platformPosition.getY(), platformPosition.getY() + 350);
    Platform platform(viewPosition, sizeOfSprite);
    PlatformView platformView(platformSprite, platform);

    return platformView;
}

//creates the border
std::vector<PlatformView> createBorders(sf::Texture *platformTexture){
    Position topPosition(960, -80);
    PlatformView topPlatform = createPlatform(2.3f, .3f, topPosition, platformTexture);

    Position leftPosition(-40, 540);
    PlatformView leftPlatform = createPlatform(.1f, 4.5f, leftPosition, platformTexture);

    Position rigthPosition(1960, 540);
    PlatformView rigthPlatform = createPlatform(.1f, 4.5f, rigthPosition, platformTexture);

    std::vector<PlatformView> platformViews;
    platformViews.push_back(topPlatform);
    platformViews.push_back(leftPlatform);
    platformViews.push_back(rigthPlatform);

    return platformViews;
}

//creates the player
PlayerView createPlayer(float sizeX,
                        float sizeY,
                        float width,
                        float height,
                        std::string pathToPlayer,
                        Position playerPosition,
                        sf::Texture *playerTexture,
                        sf::Keyboard::Key up,
                        sf::Keyboard::Key left,
                        sf::Keyboard::Key right,
                        sf::Keyboard::Key attack,
                        sf::Keyboard::Key protect,
                        sf::Keyboard::Key superAttack,
                        bool looksRight,
                        std::string namePlayerStr) {

    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.7f, 1.f);
    CoupleFloat maxSpeed(11.f, 30.f);
    float jumpHeight = 24.f;

    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    std::vector<pair<PlayerStateEnum,sf::Keyboard::Key>> keys;
    keys.push_back({jumping,up});
    keys.push_back({movingLeft,left});
    keys.push_back({movingRight,right});
    keys.push_back({attacking,attack});
    keys.push_back({defending,protect});
    keys.push_back({specialAttacking,superAttack});
    CoupleFloat sizeCouple(sizeX, sizeY);
    CoupleFloat sizeOfSprite(sizeCouple);

    CoupleFloat centerOfSprite(width, height);

    PlayerSprite playerSprite = initSpritePlayer(sizeCouple, centerOfSprite, pathToPlayer, playerPosition, playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, width, height));

    float atk = 15.f;

    Player player(namePlayerStr, atk, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player, keys, looksRight, sizeCouple);
    return playerView;
}

//Creates the healthBar
HealthBarView createHealthBar(Player player, Position posHealthBar) {
    sf::RectangleShape healthBarIn;
    sf::RectangleShape healthBarOut;

    HealthBar healthBar(player.getHealth(), posHealthBar);
    HealthBarView healthBarView(&healthBar, healthBarIn, healthBarOut);

    healthBarView.setPositionHealthBarIn();
    healthBarView.setPositionHealthBarOut();

    healthBarView.actualiseColorHealthBarIn();
    healthBarView.actualiseColorHealthBarOut();

    healthBarView.actualiseSizeHealthBarIn(player.getHealth());
    healthBarView.actualiseSizeHealthBarOut();

    return healthBarView;
}
