#ifndef PLAYERVIEWBUILDER_H
#define PLAYERVIEWBUILDER_H

#include "PlayerView.h"
#include "Player.h"
#include "CoupleFloat.h"
#include "SpriteInitializer.h"
#include "StatePlayer.h"

class PlayerViewBuilder {
    private:
        PlayerView playerView;

    public:
        PlayerViewBuilder();
        virtual ~PlayerViewBuilder();
        PlayerViewBuilder(const PlayerViewBuilder& other) = delete;
        PlayerViewBuilder& operator=(const PlayerViewBuilder& other) = delete;

        PlayerViewBuilder* reset();
        PlayerView build();

        /*We send a pointer of the current instance to work on the same builder
        AND PlayerViewBuilder isn't copyable.
        
        There is 2 reasons to this : if we return PlayerView -> player has no with... methods
        if we return void : we can't call a method on void.*/
        PlayerViewBuilder* withSprite(CoupleFloat size_, CoupleFloat center, std::string pathToPlayer, Position position, sf::Texture &texture);
        PlayerViewBuilder* withPlayer(Player player);
        PlayerViewBuilder* withKeys(sf::Keyboard::Key up,
                                    sf::Keyboard::Key left,
                                    sf::Keyboard::Key right,
                                    sf::Keyboard::Key attack,
                                    sf::Keyboard::Key protect,
                                    sf::Keyboard::Key superAttack);
        PlayerViewBuilder* withLooksRight(bool looksRight);
};

#endif // PLAYERVIEWBUILDER_H
