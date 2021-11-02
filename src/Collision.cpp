#include "Collision.h"

int directionCollision(PlayerView player, PlatformView platform) {

    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
    sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();

    //1 : Bas, 2 : Haut, 3 : Droite, 4 : Gauche
    if(playerBounds.intersects(platformBounds)) {
        // Bas
        if(     playerBounds.top > platformBounds.top
            &&  playerBounds.top + playerBounds.height > platformBounds.top + platformBounds.height
            &&  playerBounds.left < platformBounds.left + platformBounds.width
            &&  playerBounds.left + playerBounds.width > platformBounds.left
            ) {
                Position pos(player.getPlayer().getPosition().getX()-50,player.getPlayer().getPosition().getY());
                player.getPlayer().setPosition(pos);
            return 1;
        }
        // Haut
        else if(    playerBounds.top < platformBounds.top
                &&  playerBounds.top + playerBounds.height < platformBounds.top + platformBounds.height
                &&  playerBounds.left < platformBounds.left + platformBounds.width
                &&  playerBounds.left + playerBounds.width > platformBounds.left
                ) {

            return 2;
        }
        // Droite
        else if(    playerBounds.left > platformBounds.left
                &&  playerBounds.left + playerBounds.width > platformBounds.left + platformBounds.width
                &&  playerBounds.top < platformBounds.top + platformBounds.height
                &&  playerBounds.top + playerBounds.height > platformBounds.top
                ) {

            return 3;
        }
        // Gauche
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
