#include <SFML/Audio.hpp>
#include <vector>

#include "ScreenIncluder.h"
#include <iostream>

int main() {

    int FPS = 60;

    sf::Music music;
    if(!music.openFromFile("resources/audio/fight_theme.ogg")) {
        std::cout << "Music was not found" << std::endl;
    }
    music.setVolume(10.f);
    music.play();

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
    app.setFramerateLimit(FPS);

    std::vector<Screen*> screens;
	int screen = 0;

	/// Screens preparations
	MenuScreen menuScreen; // 0
	screens.push_back(&menuScreen);

	PrematchScreen prematchScreen; // 1
	screens.push_back(&prematchScreen);

	GameScreenRound gameScreenRound; // 2
	screens.push_back(&gameScreenRound);

//	GameScreenTimer gameScreenTimer; // 2
//	screens.push_back(&gameScreenTimer);

	OptionScreen optionScreen; // 3
	screens.push_back(&optionScreen);

	std::vector<std::string> data;
	//Main loop
	while (screen >= 0) {
		if(screen != 2) screen = screens[screen]->run(app, data, 0);
		else {
            data.push_back(prematchScreen.strFirstPlayerName);
            data.push_back(prematchScreen.pathSpriteFirstPlayer);
            data.push_back(prematchScreen.strSecondPlayerName);
            data.push_back(prematchScreen.pathSpriteSecondPlayer);
            screen = screens[screen]->run(app, data, prematchScreen.map_);
		}
	}

    return EXIT_SUCCESS;
}
