#include "Collision.h"

std::vector<std::vector<int>> directionCollision(PlayerView player, PlatformView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();
    std::vector<std::vector<int>> v;

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(playerBounds.intersects(platformBounds)) {
        float playerVSize = playerBounds.height;
        float playerHSize = playerBounds.width;
        float playerTop = playerBounds.top;
        float playerBottom = playerTop + playerVSize;
        float playerLeft = playerBounds.left;
        float playerRigth = playerLeft + playerHSize;

        float platformVSize = platformBounds.height;
        float platformHSize = platformBounds.width;
        float platformTop = platformBounds.top;
        float platformBottom = platformTop + platformVSize;
        float platformLeft = platformBounds.left;
        float platformRigth = platformLeft + platformHSize;

        // Right platform
            // le left du player doit etre plus petit que le rigth de la plateforme
            //le rigth du player doit etre plus grand que le rigth de la plateforme
            //le bas du joueur doit etre plus grand que le haut de la plateforme ET
            // la haut du joueur doit etre plus petit que le bas de la plateforme
        if(playerLeft < platformRigth
           &&  playerRigth > platformRigth
           &&  playerTop < platformBottom - 30
           ) {
            std::cout<<"droite ";
            std::vector <int> temp;
            temp.push_back(3);
            temp.push_back(platformRigth + std::floor(playerHSize/2) +1);
            v.push_back(temp);
        }

        // Left platform
            //le rigth du player doit etre plus grand que le left de la plateforme
            //le left du player doit etre plus petit que le lefts de la plateforme
        if(playerRigth > platformLeft
           &&  playerLeft < platformLeft
           &&  playerTop < platformBottom - 30
           ){
            std::cout<<"gauche ";
            std::vector <int> temp;
            temp.push_back(4);
            temp.push_back(platformLeft - std::floor(playerHSize/2) -1);
            v.push_back(temp);
        }


        //Bottom platform
            //le top du player doit etre plu petit que le bottom de la plateforme
            //le bottom du player doit etre plus grand que le bottom de la plateforme
        if(playerTop < platformBottom
            && playerBottom > platformBottom
            && (playerLeft < platformRigth - 10)
            && (playerRigth > platformLeft + 10)
           ) {
            std::cout<<"bas ";
            std::vector <int> temp;
            temp.push_back(1);
            temp.push_back(platformBottom + std::floor(playerVSize/2) - 1);
            v.push_back(temp);
        }
        // Top platform
            //le bottom du player doit etre plus grand que le top de la plateforme
            //le top du player doit etre plus petit que le top de la plateforme
            //la gauche du player ne doit pas etre en contact avec la paroi => doit etre plus grande que la droite de la plateforme
        if(playerBottom > platformTop
           &&  playerTop < platformTop
           && (playerLeft < platformRigth - 10)
           && (playerRigth > platformLeft + 10)
           ) {
            std::cout<<"haut ";
            std::vector <int> temp;
            temp.push_back(2);
            temp.push_back(platformTop - std::floor(playerVSize/2) + 1 );
            v.push_back(temp);
        }
        std::cout<<std::endl;
        return v;

    } else {
        std::vector <int> temp;
        temp.push_back(-1);
        temp.push_back(0);
        v.push_back(temp);
        return v;
    }
    std::vector <int> temp;
    temp.push_back(-2);
    temp.push_back(0);
    v.push_back(temp);
    return v;
}

std::vector<std::vector<int>> directionCollisionPlayers(PlayerView player, PlayerView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();
    std::vector<std::vector<int>> v;

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(playerBounds.intersects(platformBounds)) {
        float playerVSize = playerBounds.height;
        float playerHSize = playerBounds.width;
        float playerTop = playerBounds.top;
        float playerBottom = playerTop + playerVSize;
        float playerLeft = playerBounds.left;
        float playerRigth = playerLeft + playerHSize;

        float platformVSize = platformBounds.height;
        float platformHSize = platformBounds.width;
        float platformTop = platformBounds.top;
        float platformBottom = platformTop + platformVSize;
        float platformLeft = platformBounds.left;
        float platformRigth = platformLeft + platformHSize;

        // Right platform
            // le left du player doit etre plus petit que le rigth de la plateforme
            //le rigth du player doit etre plus grand que le rigth de la plateforme
        if(playerLeft < platformRigth &&  playerRigth > platformRigth) {
            std::vector <int> temp;
            temp.push_back(3);
            temp.push_back(platformRigth + std::floor(playerHSize/2) +1);
            v.push_back(temp);
        }

        // Left platform
            //le rigth du player doit etre plus grand que le left de la plateforme
            //le left du player doit etre plus petit que le lefts de la plateforme
        if(playerRigth > platformLeft &&  playerLeft < platformLeft){
            std::vector <int> temp;
            temp.push_back(4);
            temp.push_back(platformLeft - std::floor(playerHSize/2) -1);
            v.push_back(temp);
        }


        //Bottom platform
            //le top du player doit etre plu petit que le bottom de la plateforme
            //le bottom du player doit etre plus grand que le bottom de la plateforme
        if(playerTop < platformBottom && playerBottom > platformBottom) {
            std::vector <int> temp;
            temp.push_back(1);
            temp.push_back(platformBottom + std::floor(playerVSize/2) - 1);
            v.push_back(temp);
        }
        // Top platform
            //le bottom du player doit etre plus grand que le top de la plateforme
            //le top du player doit etre plus petit que le top de la plateforme
        if(playerBottom > platformTop &&  playerTop < platformTop ) {
            std::vector <int> temp;
            temp.push_back(2);
            temp.push_back(platformTop - std::floor(playerVSize/2) +1);
            v.push_back(temp);
        }

        return v;

    } else {
        std::vector <int> temp;
        temp.push_back(-1);
        temp.push_back(0);
        v.push_back(temp);
        return v;
    }
    std::vector <int> temp;
    temp.push_back(-2);
    temp.push_back(0);
    v.push_back(temp);
    return v;
}

std::vector<std::vector<std::vector<int>>> directionCollisions(PlayerView player, std::vector<PlatformView> platforms){

    std::vector<std::vector <std::vector<int>>> test;
    for(auto i : platforms){
        test.push_back(directionCollision(player, i));
    }
    return test;
}
