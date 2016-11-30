#include "Inventory.h"



Inventory::Inventory()
{
	page = 0;
	initialized = false;
}


Inventory::~Inventory()
{
}

void Inventory::BuildPages()
{
	Text blank = Text(Vector2f(0, 0), "", Vector2f(textSize, textSize));
	Text object = Text(Vector2f(0, 0), "Get Object", Vector2f(textSize, textSize));
	Text temppage[100] = {
		blank, Text(Vector2f(0,0), "STATS", Vector2f(textSize,textSize)), blank, blank, Text(Vector2f(0,0), "INVENTORY", Vector2f(textSize,textSize)), blank, blank, blank, Text(Vector2f(0,0), "MENU", Vector2f(textSize,textSize)), blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, object, blank, blank, blank, blank, blank, blank, blank
	};
	for (int i = 0; i < 100; i++) {
		page1[i] = temppage[i];
	}
	Text temppage2[100] = {
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank
	};
	for (int i = 0; i < 100; i++) {
		page2[i] = temppage2[i];
	}
	Text temppage3[100] = {
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank,
		blank, blank, blank, blank, blank, blank, blank, blank, blank, blank
	};
	for (int i = 0; i < 100; i++) {
		page3[i] = temppage3[i];
	}
}

int Inventory::Display(int health, int mana, int xp, Vector2f pos)
{
	if (!initialized) {
		BuildPages();

		BackDrop = Object(Vector2f(0, 0), Vector2f(128, 128), "Inventory");
		initialized = true;
	}
	BackDrop.position = pos - Vector2f(48, 48);
	BackDrop.draw();
	int line = 0;
	switch (page) {
		case (0) :
			line = 0;
			for (int i = 0; i < 100; i++) {
				if (page1[i].data == "STATS") {
					std::cout << line << std::endl;
				}
				page1[i].position.x = -60 + ((i%10) * 12);
				page1[i].position.y = 60 - (line * 12);
				page1[i].draw();
				if (i % 10 == 0 && i != 0) {
					
					line++;
				}
			}
			break;
		case (1) :
				for (int i = 0; i < weapons.size(); i++) {
					weapons.at(i).draw();
				}
	};
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

