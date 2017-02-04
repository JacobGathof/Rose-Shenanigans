#include "Main.h"
#include <time.h>
#include "Timer.h"
#include "Menu.h"
#include "opengl-wrapper\SFML\include\SFML\Audio.hpp"


int main() {

	srand((unsigned int)time(NULL));


	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 4;
	settings.minorVersion = 3;

	sf::RenderWindow window(sf::VideoMode(800, 800), "I'm just a nigga with a rocket launcher", sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive();

	sf::Music music;
	music.openFromFile("Resources/mus_zz_megalovania.ogg");
	music.play();

	initializeOGL();

	game.init();
	Menu::init(&game);
	Input::game = &game;


	bool running = true;
	while (running)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Timer::wait();

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
				processKeyEvent(event);
			}
			if (event.type == sf::Event::Closed){
				running = false;
			}
			else if (event.type == sf::Event::Resized){
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		game.loop(0);
		game.render();

		if (game.state == CLOSING)
			break;

		window.display();
	}

	Res::cleanResources();
	Menu::clean();

	return 0;

}

void initializeOGL() {

	std::cout << "Initializing OpenGL" << std::endl;
	
	gl3wInit();

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SIZE);
	glClearColor(0, 0, 0, 1);
	std::cout << "Initializing OpenGL Complete" << std::endl;
}


void processKeyEvent(sf::Event event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		game.state = CLOSING;
		return;
	}

	if (event.type == sf::Event::KeyPressed) {
		Input::keys[event.key.code] = true;
	}
	if (event.type == sf::Event::KeyReleased) {
		Input::keys[event.key.code] = false;
	}


}