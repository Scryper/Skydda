#include <SFML/Audio.hpp>
#include <vector>
#include "GlobalVariables.h"
#include "ScreenIncluder.h"
#include "MusicManager.h"

#include <iostream>

int GlobalVariables::FPS = 60;
float GlobalVariables::VOLUME_MUSIC = 0.f;

int main() {

    MusicManager* musicManager = MusicManager::getInstance();
    musicManager->play();

    sf::Music music;
    if(!music.openFromFile("resources/audio/fight_theme.ogg")) {
        std::cout << "Music was not found" << std::endl;
    }
    music.setVolume(GlobalVariables::VOLUME_MUSIC);
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
    app.setFramerateLimit(GlobalVariables::FPS);

    std::vector<Screen*> screens;
	int screen = 0;

	/// Screens preparations
	MenuScreen menuScreen; // 0
	screens.push_back(&menuScreen);

	PrematchScreen prematchScreen; // 1
	screens.push_back(&prematchScreen);

	GameScreenRound gameScreenRound; // 2
	screens.push_back(&gameScreenRound);

	GameScreenTimer gameScreenTimer; // 3
	screens.push_back(&gameScreenTimer);

	OptionScreen optionScreen; // 4
	screens.push_back(&optionScreen);

	std::vector<std::string> data;
	//Main loop
	while (screen >= 0) {
		if(screen == 2 || screen == 3) {
            data.push_back(prematchScreen.strFirstPlayerName);
            data.push_back(prematchScreen.pathSpriteFirstPlayer);
            data.push_back(prematchScreen.strSecondPlayerName);
            data.push_back(prematchScreen.pathSpriteSecondPlayer);
            screen = screens[screen]->run(app, data, prematchScreen.map_);
		}
		else {
            screen = screens[screen]->run(app, data, 0);
		}
	}

    return EXIT_SUCCESS;
}
