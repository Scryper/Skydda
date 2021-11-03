#include "Collision.h"

std::vector<int> directionCollision(PlayerView player, PlatformView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();
    std::vector<int> v;

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(playerBounds.intersects(platformBounds)) {
        // Bottom
        if(     playerBounds.top > platformBounds.top
            &&  playerBounds.top + playerBounds.height > platformBounds.top + platformBounds.height
            &&  playerBounds.left < platformBounds.left + platformBounds.width
            &&  playerBounds.left + playerBounds.width > platformBounds.left
            ) {
            v.push_back(1);
            v.push_back(platformBounds.top + playerBounds.height - 1);
            return v;
        }
        // Top
        else if(    playerBounds.top < platformBounds.top
                &&  playerBounds.top + playerBounds.height < platformBounds.top + platformBounds.height
                &&  playerBounds.left < platformBounds.left + platformBounds.width
                &&  playerBounds.left + playerBounds.width > platformBounds.left
                ) {
            v.push_back(2);
            v.push_back(platformBounds.top - platformBounds.height +1);
            return v;
        }
        // Right
        else if(    playerBounds.left > platformBounds.left
                &&  playerBounds.left + playerBounds.width > platformBounds.left + platformBounds.width
                &&  playerBounds.top < platformBounds.top + platformBounds.height
                &&  playerBounds.top + playerBounds.height > platformBounds.top
                ) {
            v.push_back(3);
            v.push_back(platformBounds.top + platformBounds.height);
            return v;
        }
        // Left
        else if(    playerBounds.left < platformBounds.left
                &&  playerBounds.left + playerBounds.width < platformBounds.left + platformBounds.width
                &&  playerBounds.top < platformBounds.top + platformBounds.height
                &&  playerBounds.top + playerBounds.height > platformBounds.top
                ) {
            v.push_back(4);
            v.push_back(platformBounds.top + platformBounds.height);
            return v;
        }
    } else {
        v.push_back(-1);
        v.push_back(0);
        return v;
    }
    v.push_back(-2);
    v.push_back(0);
    return v;
}

std::vector<std::vector<int>> directionCollisions(PlayerView player, std::vector<PlatformView> platforms){

    std::vector <std::vector<int>> test;
    for(auto i : platforms){
        test.push_back(directionCollision(player,i));
    }
    return test;
}
