#include "ObjectInitializer.h"

// creates the platform
PlatformView createPlatform(float sizeX, float sizeY, Position platformPosition, sf::Texture *platformTexture) {
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    sf::Sprite platformSprite = initSprite(sizeOfSprite, platformPosition, platformTexture);

    Position viewPosition(platformPosition.getY(), platformPosition.getY() + 350);
    Platform platform(viewPosition, sizeOfSprite);
    PlatformView platformView(platformSprite, platform);

    return platformView;
}

//creates the border
std::vector<PlatformView> createBorders(sf::Texture *platformTexture){
    Position topPosition(960, -50);
    PlatformView topPlatform = createPlatform(2.3f, .3f, topPosition, platformTexture);

    Position leftPosition(-100, 540);
    PlatformView leftPlatform = createPlatform(.1f, 4.5f, leftPosition, platformTexture);

    Position rigthPosition(2021, 540);
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
                        bool looksRight,
                        std::string namePlayerStr) {

    std::vector<std::vector<float>> offsetState;
    for(int i = 0; i<7;i++){
        std::vector<float> temp;
        for(int j = 0;j<2;j++){
            float temp2 = 0.f;
            temp.push_back(temp2);
        }
        offsetState.push_back(temp);
    }

    //0 = alive
    //1 = defense
    //2 = attack
    //3 = jumping
    //4 = moving left
    //5 = moving Rigth
    //6 = idle

    ///offsets
    //if not in this list, the offset is null
    //defense
    offsetState[1][0]= 15.f;//X
    offsetState[1][1]= 15.f;//Y

    //attack
    offsetState[2][0]= 15.f;//X
    offsetState[2][1]= 15.f;//y

    //jumping
    offsetState[3][0]= 15.f;
    offsetState[3][1]= 15.f;

    //idle
    offsetState[6][0]= 50.f;
    offsetState[6][1]= 50.f;

    CoupleFloat velocity(.0f, .0f);
    CoupleFloat acceleration(.8f, 1.f);
    CoupleFloat maxSpeed(14.f, 20.f);
    float jumpHeight = 25.f;
    Movement movement(velocity, acceleration, maxSpeed, jumpHeight);

    std::vector<sf::Keyboard::Key> keys;
    keys.push_back(up);
    keys.push_back(left);
    keys.push_back(right);
    keys.push_back(attack);
    keys.push_back(protect);
    CoupleFloat sizeCouple(sizeX, sizeY);
    Size sizeOfSprite(sizeCouple);

    CoupleFloat centerOfSprite(width, height);

    sf::Sprite playerSprite = initSpritePlayer(sizeCouple, centerOfSprite, pathToPlayer, playerPosition, playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, width, height));

    float atk = 50.f;

    Player player(namePlayerStr, atk, 100, playerPosition, movement);
    PlayerView playerView(playerSprite, player, keys, looksRight, sizeCouple, offsetState);
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
