#include "Collision.h"

std::vector<std::vector<int>> directionCollision(PlayerView player, PlatformView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();
    bool rigthP1 = player.isLooksRigth();


    std::vector<bool>states = player.getPlayer().getState();
    std::vector<std::vector<int>> collisions;

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(playerBounds.intersects(platformBounds)) {
        float playerLeft;
        float playerRigth;
        float halfHplayer;
        //float halfVplayer;

        float playerVSize = playerBounds.height;
        float playerHSize = playerBounds.width;
        float playerTop = playerBounds.top;
        float playerBottom = playerTop + playerVSize;

        //si le joueur regarde a droite, le baton est a droite
        if(rigthP1==true){
            playerLeft = playerBounds.left;
            playerRigth = playerLeft + playerHSize;
            halfHplayer = std::floor(playerRigth - playerLeft);
        }
        else{
            playerLeft = playerBounds.left;
            playerRigth = playerLeft + playerHSize;
            halfHplayer = std::floor(playerRigth - playerLeft);
        }

        float platformVSize = platformBounds.height;
        float platformHSize = platformBounds.width;
        float platformTop = platformBounds.top;
        float platformBottom = platformTop + platformVSize;
        float platformLeft = platformBounds.left;
        float platformRigth = platformLeft + platformHSize;

        /// Right platform
        // player's left should be < than platform's right
        // player's right should be > than platform's right
        // player's bottom should be > than platform's top
        // player's top should be < than platform's bottom
        if(playerLeft < platformRigth
           &&  playerRigth > platformRigth
           &&  playerTop < platformBottom - 30
           &&  playerBottom > platformTop + 30
           ) {
            std::vector <int> tmp;
            tmp.push_back(3);
            float value = platformRigth + halfHplayer + 1;
            tmp.push_back(value);
            collisions.push_back(tmp);
        }

        /// Left platform
        // player's right should be > than platform's left
        // player's left should be < than platform's left
        if(playerRigth > platformLeft
           &&  playerLeft < platformLeft
           &&  playerTop < platformBottom - 30
           && playerBottom > platformTop + 30
           ){
            std::vector <int> tmp;
            tmp.push_back(4);
            float value = platformLeft - halfHplayer - 1;
            tmp.push_back(value);
            collisions.push_back(tmp);
        }

        /// Bottom platform
        // player's top should be < than platform's bottom
        // player's bottom should be > than platform's bottom
        if(playerTop < platformBottom
            && playerBottom > platformBottom
            && (playerLeft < platformRigth - 10)
            && (playerRigth > platformLeft + 10)
           ) {
            std::vector <int> tmp;
            tmp.push_back(1);
            tmp.push_back(platformBottom + std::floor(playerVSize / 2) - 1);
            collisions.push_back(tmp);
        }

        /// Top platform
        // player's bottom shouuld be > than platform's bottom
        // player's top shouuld be < than platform's top
        // player's left should not touch border -> should be > than platform's right
        if(playerBottom > platformTop
           &&  playerTop < platformTop
           && (playerLeft < platformRigth - 10)
           && (playerRigth > platformLeft + 10)
           ) {
            std::vector <int> tmp;
            tmp.push_back(2);
            tmp.push_back(platformTop - std::floor(playerVSize / 2) + 1);
            collisions.push_back(tmp);
        }
        return collisions;

    } else {
        std::vector <int> tmp;
        tmp.push_back(-1);
        tmp.push_back(0);
        collisions.push_back(tmp);
        return collisions;
    }
    std::vector <int> tmp;
    tmp.push_back(-2);
    tmp.push_back(0);
    collisions.push_back(tmp);
    return collisions;
}

std::vector<std::vector<int>> directionCollisionPlayers(PlayerView playerview1, PlayerView playerview2) {
    sf::FloatRect player1Bounds = playerview1.getSprite().getGlobalBounds();
    sf::FloatRect player2Bounds = playerview2.getSprite().getGlobalBounds();
    std::vector<std::vector<int>> collisions;

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(player1Bounds.intersects(player2Bounds)) {
        float playerVSize = player1Bounds.height;
        float playerHSize = player1Bounds.width;
        float playerTop = player1Bounds.top;
        float playerBottom = playerTop + playerVSize;
        float playerLeft = player1Bounds.left;
        float playerRigth = playerLeft + playerHSize;

        float platformVSize = player2Bounds.height;
        float platformHSize = player2Bounds.width;
        float platformTop = player2Bounds.top;
        float platformBottom = platformTop + platformVSize;
        float platformLeft = player2Bounds.left;
        float platformRigth = platformLeft + platformHSize;

        /// Right
        // player 1's left should be < than player 2's right
        // player 1's right should be > than player 2's right
        // player 1's bottom should be > than player 2's top
        // player 1's top should be < than player 2's bottom
        if(playerLeft < platformRigth
           &&  playerRigth > platformRigth
           &&  playerTop < platformBottom
           &&  playerBottom > platformTop
           ) {
            std::vector <int> tmp;
            tmp.push_back(3);
            collisions.push_back(tmp);
        }

        /// Left
        // player 1's right should be > than player 2's left
        // player 1's left should be < than player 2's left
        if(playerRigth > platformLeft
           &&  playerLeft < platformLeft
           &&  playerTop < platformBottom
           && playerBottom > platformTop
           ){
            std::vector <int> tmp;
            tmp.push_back(4);
            collisions.push_back(tmp);
        }

        /// Bottom
        // player 1's top should be < than player 2's bottom
        // player 1's bottom should be > than player 2's bottom
        if(playerTop < platformBottom
            && playerBottom > platformBottom
            && (playerLeft < platformRigth )
            && (playerRigth > platformLeft)
           ) {
            std::vector <int> tmp;
            tmp.push_back(1);
            collisions.push_back(tmp);
        }

        /// Top
        // player 1's bottom shouuld be > than player 2's bottom
        // player 1's top shouuld be < than player 2's top
        // player 1's left should not touch border -> should be > than player 2's right
        if(playerBottom > platformTop
           &&  playerTop < platformTop
           && (playerLeft < platformRigth)
           && (playerRigth > platformLeft)
           ) {
            std::vector <int> tmp;
            tmp.push_back(2);
            collisions.push_back(tmp);
        }
        return collisions;

    } else {
        std::vector <int> tmp;
        tmp.push_back(-1);
        collisions.push_back(tmp);
        return collisions;
    }
    std::vector <int> tmp;
    tmp.push_back(-2);
    collisions.push_back(tmp);
    return collisions;
}

std::vector<std::vector<std::vector<int>>> directionCollisions(PlayerView player, std::vector<PlatformView> platforms){
    std::vector<std::vector<std::vector<int>>> collisions;
    for(PlatformView platformView : platforms){
        collisions.push_back(directionCollision(player, platformView));
    }
    return collisions;
}
