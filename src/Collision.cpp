#include "Collision.h"

//return an array of coordinate based on collision direction
//collisions between a plateform and a player
CollisionVector directionCollision(PlayerView player, PlatformView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalHitbox();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();

    CollisionVector collisions;
    bool looksRight = player.isLooksRigth();


    if(playerBounds.intersects(platformBounds)) {

        //initialize variables
        float playerLeft;
        float playerRigth;

        float playerVSize = playerBounds.height;
        float playerHSize = playerBounds.width;
        float playerTop = playerBounds.top;
        float playerBottom = playerTop + playerVSize;

        playerLeft = playerBounds.left;
        playerRigth = playerLeft + playerHSize;

        float platformVSize = platformBounds.height;
        float platformHSize = platformBounds.width;
        float platformTop = platformBounds.top;
        float platformBottom = platformTop + platformVSize;
        float platformLeft = platformBounds.left;
        float platformRigth = platformLeft + platformHSize;

        /// col with the Right of platform
        // player's left should be < than platform's right
        // player's right should be > than platform's right
        // player's bottom should be > than platform's top
        // player's top should be < than platform's bottom
        if(playerLeft < platformRigth
           &&  playerRigth > platformRigth
           &&  playerTop < platformBottom - 30
           &&  playerBottom > platformTop + 30
           ) {
            DisplacementPerCollision tmp;
            tmp.first=rigthCol;
            float value = platformRigth;
            if(looksRight)value += playerHSize;
            tmp.second=value;
            collisions.push_back(tmp);
        }

        /// col with the Left of platform
        // player's right should be > than platform's left
        // player's left should be < than platform's left
        if(playerRigth > platformLeft
           &&  playerLeft < platformLeft
           &&  playerTop < platformBottom - 30
           && playerBottom > platformTop + 30
           ){
            DisplacementPerCollision tmp;
            tmp.first = leftCol;
            float value = platformLeft;
            if(!looksRight)value -= playerHSize;
            tmp.second=value;
            collisions.push_back(tmp);
        }



        /// col with the Bottom of platform
        // player's top should be < than platform's bottom
        // player's bottom should be > than platform's bottom
        if(playerTop < platformBottom
            && playerBottom > platformBottom
            && (playerLeft < platformRigth - 10)
            && (playerRigth > platformLeft + 10)
           ) {
            DisplacementPerCollision tmp;
            tmp.first=bottom;
            tmp.second=(platformBottom + std::floor(playerVSize / 3) - 1);
            collisions.push_back(tmp);
        }

        /// col with the Top of platform
        // player's bottom shouuld be > than platform's bottom
        // player's top shouuld be < than platform's top
        // player's left should not touch border -> should be > than platform's right
        if(playerBottom > platformTop
           &&  playerTop < platformTop
           && (playerLeft < platformRigth - 10)
           && (playerRigth > platformLeft + 10)
           ) {
            DisplacementPerCollision tmp;
            tmp.first=top;
            tmp.second=(platformTop - std::floor(playerVSize / 2) + 1);
            collisions.push_back(tmp);
        }
        return collisions;

    } else {
        DisplacementPerCollision tmp;
        tmp.first=incorrectCol;
        tmp.second=0;
        collisions.push_back(tmp);
        return collisions;
    }
}


//return an array of coordinate based on collision direction (left and rigth)
//collisions between two players
CollisionVector directionCollisionPlayers(PlayerView playerview1, PlayerView playerview2) {
    sf::FloatRect player1Bounds = playerview1.getSprite().getGlobalBounds();
    sf::FloatRect player2Bounds = playerview2.getSprite().getGlobalHitbox();

    //as the collision sprite of a player is too narrow to hit consistantly,
    //this margin allows the user to hit a little further than the hitbox of the character
    int marge = 20;

    CollisionVector collisions;

    if(player1Bounds.intersects(player2Bounds)) {
        float player1VSize = player1Bounds.height;
        float player1HSize = player1Bounds.width;

        float player1Top = player1Bounds.top;
        float player1Bottom = player1Top + player1VSize;
        float player1Left = player1Bounds.left;
        float player1Rigth = player1Left + player1HSize;

        float player2VSize = player2Bounds.height;
        float player2HSize = player2Bounds.width;

        float player2Top = player2Bounds.top;
        float player2Bottom = player2Top + player2VSize;
        float player2Left = player2Bounds.left;
        float player2Rigth = player2Left + player2HSize;


        /// col with the Right of the first player
        // player 1's left should be < than player 2's right
        // player 1's right should be > than player 2's right
        // player 1's bottom should be > than player 2's top
        // player 1's top should be < than player 2's bottom
        if(player1Left < player2Rigth - marge
           &&  player1Rigth > player2Rigth + marge
           &&  player1Top < player2Bottom
           &&  player1Bottom > player2Top
           ) {
            DisplacementPerCollision tmp;
            tmp.first=rigthCol;
            tmp.second=0;
            collisions.push_back(tmp);
        }

        /// col with the Left of the first player
        // player 1's right should be > than player 2's left
        // player 1's left should be < than player 2's left
        if(player1Rigth > player2Left + marge
           &&  player1Left < player2Left - marge
           &&  player1Top < player2Bottom
           && player1Bottom > player2Top
           ){
            DisplacementPerCollision tmp;
            tmp.first=leftCol;
            tmp.second=0;
            collisions.push_back(tmp);
        }
        return collisions;

    } else {
        DisplacementPerCollision tmp;
            tmp.first=incorrectCol;
            tmp.second=0;
            collisions.push_back(tmp);
        return collisions;
    }
}

//return an array to compute collisions of a player and an array of platforms
std::vector<CollisionVector> directionCollisions(PlayerView player, std::vector<PlatformView> platforms){
    std::vector<CollisionVector> collisions;
    for(PlatformView platformView : platforms){
        collisions.push_back(directionCollision(player, platformView));
    }
    return collisions;
}
