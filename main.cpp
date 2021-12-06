#include <SFML/Audio.hpp>
#include <vector>
#include "GlobalVariables.h"
#include "ScreenIncluder.h"
#include "MusicManager.h"
#include "SoundManager.h"

#include <iostream>

int main() {
    MusicManager* musicManager = MusicManager::getInstance();
    musicManager->play();

    // Create the main window
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow app(
        sf::VideoMode(
            desktopMode.width,
            desktopMode.height,
            desktopMode.bitsPerPixel),
        "Skydda",
        sf::Style::Fullscreen
    );

    app.setFramerateLimit(GlobalVariables::FPS);

    std::vector<Screen*> screens;
	int screen = 0;

    /// Screens preparations
    MenuScreen menuScreen; // 0
    screens.push_back(&menuScreen);

    PrematchScreen prematchScreen; // 1
    screens.push_back(&prematchScreen);

    OptionScreen optionScreen; // 2
    screens.push_back(&optionScreen);

	std::vector<std::string> data;
	//Main loop
	while (screen >= 0) {
        data.clear();

        GameScreenRound gameScreenRound; // 3
        screens.push_back(&gameScreenRound);

        GameScreenTimer gameScreenTimer; // 4
        screens.push_back(&gameScreenTimer);

		if(screen == 3 || screen == 4) {
            data.push_back(prematchScreen.strFirstPlayerName);
            data.push_back(prematchScreen.pathSpriteFirstPlayer);
            data.push_back(prematchScreen.strSecondPlayerName);
            data.push_back(prematchScreen.pathSpriteSecondPlayer);
            screen = screens[screen]->run(app, data, prematchScreen.map_);
		}
		else {
            screen = screens[screen]->run(app, data, 0);
		}
        screens.erase(screens.end()-1);
        screens.erase(screens.end()-1);
	}

	delete musicManager;
    return EXIT_SUCCESS;
}
