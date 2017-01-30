#include "Menu.h"
#include "Renderer.h"


Text* Menu::menuItems[4];
int Menu::selectedIndex=0;
Game * Menu::game;

Menu::Menu()
{
	

}


Menu::~Menu()
{
}

void Menu::setSelectedIndex(int i)
{
	menuItems[selectedIndex]->color = Color(1, 1, 1);
	selectedIndex += i;
	if (selectedIndex < 0) selectedIndex = 0;
	if (selectedIndex > 3) selectedIndex = 3;
	menuItems[selectedIndex]->color = Color(0.0f, 0.25f, 1.0f);
}

void Menu::actOnSelection(){

	if (selectedIndex == 1) {
		game->state = CLOSING;
	}
	if (selectedIndex == 0) {
		game->state = FREE;
	}

}

void Menu::init(Game* ga)
{
	game = ga;
	menuItems[0] = new Text(Vector2f(0, 30), "Start", Vector2f(10, 10), true, Color(1, 1, 1));
	menuItems[1] = new Text(Vector2f(0, 10), "Exit", Vector2f(10, 10), true, Color(1, 1, 1));
	menuItems[2] = new Text(Vector2f(0, -10), "Settings", Vector2f(10, 10), true, Color(1, 1, 1));
	menuItems[3] = new Text(Vector2f(0, -30), "Credits", Vector2f(10, 10), true, Color(1,1,1));
	setSelectedIndex(0);
}

void Menu::clean()
{
	for (int i = 0; i < 4; i++) {
		delete menuItems[i];
	}
}

void Menu::render(){

	Renderer::renderMenu();

}

void Menu::update()
{
}
