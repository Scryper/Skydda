#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "ScreenIncluder.h"

int main() {
//    sf::Music music;
//    if(!music.openFromFile("resources/audio/fight_theme.ogg")) {
//        cout << "Music was not found" << endl;
//    }
//    music.setVolume(10.f);
//    music.play();

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
    app.setFramerateLimit(60);

    std::vector<Screen*> screens;
	int screen = 0;

	//Screens preparations
	MenuScreen menuScreen;
	screens.push_back(&menuScreen);
	GameScreen gameScreen;
	screens.push_back(&gameScreen);

	//Main loop
	while (screen >= 0) {
		screen = screens[screen]->run(app);
	}

    return EXIT_SUCCESS;
}
