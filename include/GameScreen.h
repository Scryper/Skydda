#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "PlayerView.h"
#include "PlatformView.h"
#include "Collision.h"
#include "ObjectInitializer.h"
#include "MapView.h"
#include "HealthBar.h"
#include "HealthBarView.h"

class GameScreen : public Screen {
    public:
        GameScreen();
        virtual ~GameScreen();

        virtual int run(sf::RenderWindow &app);
};

#endif // GAMESCREEN_H
