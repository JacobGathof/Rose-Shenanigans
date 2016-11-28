#include "Inventory.h"



Inventory::Inventory()
{
	page = 0;
	initialized = false;
}


Inventory::~Inventory()
{
}

int Inventory::Display(int health, int mana, int xp, Vector2f pos)
{
	if (!initialized) {
		tab1 = Text(Vector2f(-45, 55), "Stats", Vector2f(5, 5));
		tab2 = Text(Vector2f(-15, 55), "Inventory", Vector2f(5, 5));
		tab3 = Text(Vector2f(30, 55), "Skills", Vector2f(5, 5));
		BackDrop = Object(Vector2f(0, 0), Vector2f(128, 128), "Inventory");
		initialized = true;
	}
	BackDrop.position = pos - Vector2f(48,48);
	BackDrop.draw();
	tab1.draw();
	tab2.draw();
	tab3.draw();
	switch (page)
		case (0) : 
			

		case (1) :
			for (int i = 0; i < weapons.size(); i++) {
				weapons.at(i).draw();
			}
			

	return 0;
}

void Inventory::addWeapon(Weapon weapon)
{
	weapons.push_back(weapon);
}

void Inventory::discard(Weapon weapon)
{
	for (int i = 0; i < weapons.size(); i++) {
		if (weapons.at(i).texture == weapon.texture) {
			weapons.erase(weapons.begin() + i);
			break;
		}
	}
}
