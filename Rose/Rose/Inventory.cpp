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
		blank, blank, object, blank, blank, object, blank, blank, blank, blank,
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
	//std::cout << selectedIndex << std::endl;
	page1[selectedIndex] = Text(Vector2f(0, 0), "hello", Vector2f(0, 0));
	BackDrop.position = pos - Vector2f(48, 48);
	BackDrop.draw();
	int line = 0;
	switch (page) {
		case (0) :
			line = 0;
			for (int i = 0; i < 100; i++) {
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

void Inventory::MoveRight()
{
	int oldIndex = selectedIndex;
	selectedIndex++;
	int i = 0;
	Text * currentPage = GetCurrentPage();
	while (i != 1) {
		if (selectedIndex < 0 || selectedIndex > 100) {
			selectedIndex = oldIndex;
			return;
		}
		if (currentPage[selectedIndex].data == "") {
			selectedIndex++;
		}
		else {
			i = 1;
		}
	}
}

void Inventory::MoveLeft()
{
	int oldIndex = selectedIndex;
	selectedIndex--;
	int i = 0;
	Text * currentPage = GetCurrentPage();
	while (i != 1) {
		if (selectedIndex < 0 || selectedIndex > 100) {
			selectedIndex = oldIndex;
			return;
		}
		if (currentPage[selectedIndex].data == "") {
			selectedIndex--;
		}
		else {
			i = 1;
		}
	}
}

void Inventory::MoveUp()
{
	int oldIndex = selectedIndex;
	selectedIndex -= 10;
	int i = 0;
	Text * currentPage = GetCurrentPage();
	while (i != 1) {
		if (selectedIndex < 0 || selectedIndex > 100) {
			selectedIndex = oldIndex;
			return;
		}
		if (currentPage[selectedIndex].data == "") {
			selectedIndex++;
		}
		else {
			i = 1;
		}
	}
}

void Inventory::MoveDown()
{
	int oldIndex = selectedIndex;
	selectedIndex += 10;
	int i = 0;
	Text * currentPage = GetCurrentPage();
	while (i != 1) {
		if (selectedIndex < 0 || selectedIndex > 100) {
			selectedIndex = oldIndex;
			return;
		}
		if (currentPage[selectedIndex].data == "") {
			selectedIndex++;
		}
		else {
			i = 1;
		}
	}
}

void Inventory::Select()
{
}

Text * Inventory::GetCurrentPage()
{
	if (page == 0) {
		return page1;
	}
	else if (page == 1) {
		return page2;
	}
	else if (page == 2) {
		return page3;
	}
	return nullptr;
}

