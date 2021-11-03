#include "Collision.h"

int directionCollision(PlayerView player, PlatformView platform) {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();

    //1 : Bottom, 2 : Top, 3 : Right, 4 : Left
    if(playerBounds.intersects(platformBounds)) {
        // Bottom
        if(     playerBounds.top > platformBounds.top
            &&  playerBounds.top + playerBounds.height > platformBounds.top + platformBounds.height
            &&  playerBounds.left < platformBounds.left + platformBounds.width
            &&  playerBounds.left + playerBounds.width > platformBounds.left
            ) {
                Position pos(player.getPlayer().getPosition().getX()-50,player.getPlayer().getPosition().getY());
                player.getPlayer().setPosition(pos);
            return 1;
        }
        // Top
        else if(    playerBounds.top < platformBounds.top
                &&  playerBounds.top + playerBounds.height < platformBounds.top + platformBounds.height
                &&  playerBounds.left < platformBounds.left + platformBounds.width
                &&  playerBounds.left + playerBounds.width > platformBounds.left
                ) {
            return 2;
        }
        // Right
        else if(    playerBounds.left > platformBounds.left
                &&  playerBounds.left + playerBounds.width > platformBounds.left + platformBounds.width
                &&  playerBounds.top < platformBounds.top + platformBounds.height
                &&  playerBounds.top + playerBounds.height > platformBounds.top
                ) {
            return 3;
        }
        // Left
        else if(    playerBounds.left < platformBounds.left
                &&  playerBounds.left + playerBounds.width < platformBounds.left + platformBounds.width
                &&  playerBounds.top < platformBounds.top + platformBounds.height
                &&  playerBounds.top + playerBounds.height > platformBounds.top
                ) {
            return 4;
        }
    } else {
        return -1;
    }
    return -2;
}

std::vector<int> directionCollisions(PlayerView player, std::vector<PlatformView> platforms){

    std::vector <int> test;
    for(auto i : platforms){
        test.push_back(directionCollision(player,i));
    }
    return test;
}
