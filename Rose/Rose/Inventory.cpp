#include "Inventory.h"



Inventory::Inventory()
{
	page = 0;
	//BackDrop = Object(Vector2f(0, 0), Vector2f(100, 100), "House");
}


Inventory::~Inventory()
{
}

int Inventory::Display(int health, int mana, int xp, Vector2f pos)
{
	//BackDrop.position = pos;
	//BackDrop.draw();
	switch (page)
		case (0) :
			for (int i = 0; i < weapons.size(); i++) {
				std::cout << weapons.at(i).texture << std::endl;
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
